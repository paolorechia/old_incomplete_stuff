
#include <caffe/caffe.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iosfwd>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <stdio.h>


enum NORMALIZATION_TYPES
{
	MINMAX=1,
	MEAN_IMAGE
};

NORMALIZATION_TYPES normalizatioType;

using namespace caffe;  // NOLINT(build/namespaces)
using std::string;
using namespace std;

/* Pair (label, confidence) representing a prediction. */
typedef std::pair<string, float> Prediction;

class Classifier {
 public:
  Classifier(const string& model_file,
             const string& trained_file,
             const string& mean_file,
             const string& label_file);

  std::vector<Prediction> Classify(const cv::Mat& img, int N = 5);

 private:
  void SetMean(const string& mean_file);

  std::vector<float> Predict(const cv::Mat& img);

  void WrapInputLayer(std::vector<cv::Mat>* input_channels);

  void Preprocess(const cv::Mat& img,
                  std::vector<cv::Mat>* input_channels);

 private:
  shared_ptr<Net<float> > net_;
  cv::Size input_geometry_;
  int num_channels_;
  cv::Mat mean_;
  std::vector<string> labels_;
};

Classifier::Classifier(const string& model_file,
                       const string& trained_file,
                       const string& mean_file,
                       const string& label_file) {
#ifdef CPU_ONLY
  Caffe::set_mode(Caffe::CPU);
#else
  Caffe::set_mode(Caffe::GPU);
#endif

  /* Load the network. */
  net_.reset(new Net<float>(model_file, TEST));
  net_->CopyTrainedLayersFrom(trained_file);

  CHECK_EQ(net_->num_inputs(), 1) << "Network should have exactly one input.";
  CHECK_EQ(net_->num_outputs(), 1) << "Network should have exactly one output.";

  Blob<float>* input_layer = net_->input_blobs()[0];
  num_channels_ = input_layer->channels();
  CHECK(num_channels_ == 3 || num_channels_ == 1)
    << "Input layer should have 1 or 3 channels.";
  input_geometry_ = cv::Size(input_layer->width(), input_layer->height());

  /* Load the binaryproto mean file. */
  if(normalizatioType == MEAN_IMAGE)
     SetMean(mean_file);

  /* Load labels. */
  std::ifstream labels(label_file.c_str());
  CHECK(labels) << "Unable to open labels file " << label_file;
  string line;
  while (std::getline(labels, line))
    labels_.push_back(string(line));

  Blob<float>* output_layer = net_->output_blobs()[0];
  CHECK_EQ(labels_.size(), output_layer->channels())
    << "Number of labels is different from the output layer dimension.";
}

static bool PairCompare(const std::pair<float, int>& lhs,
                        const std::pair<float, int>& rhs) {
  return lhs.first > rhs.first;
}

/* Return the indices of the top N values of vector v. */
static std::vector<int> Argmax(const std::vector<float>& v, int N) {
  std::vector<std::pair<float, int> > pairs;
  for (size_t i = 0; i < v.size(); ++i)
    pairs.push_back(std::make_pair(v[i], i));
  std::partial_sort(pairs.begin(), pairs.begin() + N, pairs.end(), PairCompare);

  std::vector<int> result;
  for (int i = 0; i < N; ++i)
    result.push_back(pairs[i].second);
  return result;
}

/* Return the top N predictions. */
std::vector<Prediction> Classifier::Classify(const cv::Mat& img, int N) {
  std::vector<float> output = Predict(img);

  std::vector<int> maxN = Argmax(output, N);
  std::vector<Prediction> predictions;
  for (int i = 0; i < N; ++i) {
    int idx = maxN[i];
    predictions.push_back(std::make_pair(labels_[idx], output[idx]));
  }

  return predictions;
}

/* Load the mean file in binaryproto format. */
void Classifier::SetMean(const string& mean_file) {
  BlobProto blob_proto;
  ReadProtoFromBinaryFileOrDie(mean_file.c_str(), &blob_proto);

  /* Convert from BlobProto to Blob<float> */
  Blob<float> mean_blob;
  mean_blob.FromProto(blob_proto);
  CHECK_EQ(mean_blob.channels(), num_channels_)
    << "Number of channels of mean file doesn't match input layer.";

  /* The format of the mean file is planar 32-bit float BGR or grayscale. */
  std::vector<cv::Mat> channels;
  float* data = mean_blob.mutable_cpu_data();
  for (int i = 0; i < num_channels_; ++i) {
    /* Extract an individual channel. */
    cv::Mat channel(mean_blob.height(), mean_blob.width(), CV_32FC1, data);
    channels.push_back(channel);
    data += mean_blob.height() * mean_blob.width();
  }

  /* Merge the separate channels into a single image. */
  cv::Mat mean;
  cv::merge(channels, mean);

  /* Compute the global mean pixel value and create a mean image
   * filled with this value. */
  cv::Scalar channel_mean = cv::mean(mean);
  mean_ = cv::Mat(input_geometry_, mean.type(), channel_mean);
}

std::vector<float> Classifier::Predict(const cv::Mat& img) {
  Blob<float>* input_layer = net_->input_blobs()[0];
  input_layer->Reshape(1, num_channels_,
                       input_geometry_.height, input_geometry_.width);
  /* Forward dimension change to all layers. */
  net_->Reshape();

  std::vector<cv::Mat> input_channels;
  WrapInputLayer(&input_channels);

  Preprocess(img, &input_channels);

  net_->ForwardPrefilled();

  /* Copy the output layer to a std::vector */
  Blob<float>* output_layer = net_->output_blobs()[0];
  const float* begin = output_layer->cpu_data();
  const float* end = begin + output_layer->channels();
  return std::vector<float>(begin, end);
}

/* Wrap the input layer of the network in separate cv::Mat objects
 * (one per channel). This way we save one memcpy operation and we
 * don't need to rely on cudaMemcpy2D. The last preprocessing
 * operation will write the separate channels directly to the input
 * layer. */
void Classifier::WrapInputLayer(std::vector<cv::Mat>* input_channels) {
  Blob<float>* input_layer = net_->input_blobs()[0];

  int width = input_layer->width();
  int height = input_layer->height();
  float* input_data = input_layer->mutable_cpu_data();
  for (int i = 0; i < input_layer->channels(); ++i) {
    cv::Mat channel(height, width, CV_32FC1, input_data);
    input_channels->push_back(channel);
    input_data += width * height;
  }
}

void Classifier::Preprocess(const cv::Mat& img,
                            std::vector<cv::Mat>* input_channels) {
  /* Convert the input image to the input image format of the network. */
  cv::Mat sample;
  if (img.channels() == 3 && num_channels_ == 1)
    cv::cvtColor(img, sample, CV_BGR2GRAY);
  else if (img.channels() == 4 && num_channels_ == 1)
    cv::cvtColor(img, sample, CV_BGRA2GRAY);
  else if (img.channels() == 4 && num_channels_ == 3)
    cv::cvtColor(img, sample, CV_BGRA2BGR);
  else if (img.channels() == 1 && num_channels_ == 3)
    cv::cvtColor(img, sample, CV_GRAY2BGR);
  else
    sample = img;

  cv::Mat sample_resized;
  if (sample.size() != input_geometry_)
    cv::resize(sample, sample_resized, input_geometry_);
  else
    sample_resized = sample;

  cv::Mat sample_float;
  if (num_channels_ == 3)
    sample_resized.convertTo(sample_float, CV_32FC3);
  else
    sample_resized.convertTo(sample_float, CV_32FC1);

  cv::Mat sample_normalized;
  
   //ImageNet: Normalizacao pela subtração da imagem media  
  if(normalizatioType == MEAN_IMAGE)
	cv::subtract(sample_float, mean_, sample_normalized);
  else 	if(normalizatioType == MINMAX)
	cv::normalize(sample_float,sample_float,0,1,cv::NORM_MINMAX, CV_32F);

  /* This operation will write the separate BGR planes directly to the
   * input layer of the network because it is wrapped by the cv::Mat
   * objects in input_channels. */
  cv::split(sample_float, *input_channels);

  CHECK(reinterpret_cast<float*>(input_channels->at(0).data)
        == net_->input_blobs()[0]->cpu_data())
    << "Input channels are not wrapping the input layer of the network.";
}

int main(int argc, char** argv) {
  if (argc < 8) {
    std::cerr << "Usage: " << argv[0]
              << " deploy.prototxt network.caffemodel"
              << " mean.binaryproto labels.txt list_of_files.txt base_path NormalizationType: MINMAX | MEAN_IMAGE [nPREDICTIONSS]" << std::endl;
    return 1;
  }

  ::google::InitGoogleLogging(argv[0]);
  
  char list_file[1204],base_path[1024];
  int error=0, ok=0, nPREDS=1 ;
  string model_file   = argv[1];
  string trained_file = argv[2];
  string mean_file    = argv[3];
  string label_file   = argv[4];
  strcpy(list_file,argv[5]);
  strcpy(base_path,argv[6]);
	
  if(strcmp("MINMAX",argv[7]) == 0)
	normalizatioType=MINMAX;
  else if(strcmp("MEAN_IMAGE",argv[7]) == 0)
	normalizatioType=MEAN_IMAGE;
  else
  {
        cout << "==>CONFIG ERROR: NormalizationType \"" << argv[7] << "\" unrecognized. Use MINMAX or MEAN_IMAGE <== CONFIG ERROR" << endl;
	return -1;
  }

  if(argc > 8) //Se foi informado o numero de Preds!!, senao o default é 1
     nPREDS=atoi(argv[8]);
  else
     nPREDS = 1;

  Classifier classifier(model_file, trained_file, mean_file, label_file);
  
  FILE *fp = fopen(list_file,"r");
  if(!fp)
  {
	 fprintf(stderr,"Can't read %s\n",list_file);
	 return 0;   
  }

  int confusionMatrix[10][10];
  for (int i = 0; i < 10; i++){
    for (int j = 0; j < 10; j++){
      confusionMatrix[i][j]=0;
    }
  }
  
  while(!feof(fp))
  {
	  char file[256];
	  char fullpath[1024];
	  int label;
	  
	  fscanf(fp,"%s %d\n",file,&label);
	  
	  
	  sprintf(fullpath,"%s/%s", base_path, file); 
	  
//	  std::cout << "---------- Prediction for "
//				<< file << " ----------" << std::endl;

	  cv::Mat img = cv::imread(fullpath, -1);
	  img.convertTo(img, CV_32F);



	  CHECK(!img.empty()) << "Unable to decode image " << file;
	  std::vector<Prediction> predictions = classifier.Classify(img,nPREDS);


	
	img.release();
	if(predictions.size() > 0)
	{	
		//TOP1
		std::size_t pos = predictions[0].first.find(" ");      //Pego o rotulo da classe
		std::string predictClass = predictions[0].first.substr (0,pos);
		std::string classLabel = predictions[0].first.substr (pos+1);

		int pred = atoi(predictClass.c_str());
		if(pred == label)
			ok++;
		else
	        {
		 	error++;
			//cout << "Error --> ";
		}
		
        confusionMatrix[int(pred)][int(label)]+=1;

		
//		std::cout << fullpath << " Label:" << std::setw(2) << std::setfill('0') << label 
//			<< " Preds:" << std::setw(2) << std::setfill('0') << pred << " ClassName:" << classLabel << " Score:" << std::fixed << std::setprecision(4) << predictions[0].second 
//			<< " | " ;

		//TOP K
                for(int k=0; k<(int)predictions.size(); k++)
		{
		        std::size_t pos = predictions[k].first.find(" ");      //Pego o rotulo da classe
	                std::string predictClass = predictions[k].first.substr (0,pos);
	                std::string classLabel = predictions[k].first.substr (pos+1);

	       	        int pred = atoi(predictClass.c_str());
//			cout << " [Preds:" << std::setw(2) << std::setfill('0') << pred << " ClassName:" << classLabel << " Score:" << std::fixed << std::setprecision(4) << predictions[k].second << "]";
                        
		
		}


//		cout << endl;

	}
	
  }

   int total = ok + error;

   float acc = (float) ok / (float) total;
   cout << acc << endl;
   cout <<  "Precisao: " << std::fixed << std::setprecision(4) << acc << " ( " << ok << " / " << total << " ) " << "\\\\" << endl;	
   cout << "Matriz de confusao: \\\\" << std::endl;
   cout << "\\begin{center}\n\\begin{tabular}" << std::endl;
   cout << "{|";
   for (int i = 0; i < 10; i++){
      cout << "c|" ;
   }
   cout <<"}\n" << endl;
   cout << "\\hline" << endl;
   for (int i = 0; i < 10; i++){
      for (int j = 0; j < 10; j++){
         if (j == 9){
            cout << confusionMatrix[i][j] << "\\\\ \n \\hline";
         }
         else {
            cout << confusionMatrix[i][j] << "& ";
         }
      }
      cout << std::endl;
   }
   cout << "\\end{tabular}\n\\end{center}" << endl;
}
