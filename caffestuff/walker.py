#!/usr/bin/python
from ConfigParser import SafeConfigParser
import os
import jinja2
import sys
import pprint
import subprocess
import numpy
import matplotlib.mlab as mlab
import matplotlib.pyplot as plt


def render(tpl_path, context):
    path, filename = os.path.split(tpl_path)
    return jinja2.Environment(
        loader=jinja2.FileSystemLoader(path or './')
    ).get_template(filename).render(context)

# Tries different networks and store results

def printLatex(dictionary, filepointer):
    for key, value in dictionary.iteritems():
        filepointer.write(str(key) + ": " + str(value) + "\\\\ \n")



class FakeSecHead(object):
    def __init__(self, fp):
        self.fp = fp
        self.sechead = '[asection]\n'

    def readline(self):
        if self.sechead:
            try: 
                return self.sechead
            finally: 
                self.sechead = None
        else: 
            return self.fp.readline()

def main():
    prototxt = '/home/paolo/caffe/dummy/models/lenet_solver.prototxt'
    cp =SafeConfigParser()
    cp.readfp(FakeSecHead(open(prototxt)))
    cp.set('asection', 'max_iter', '10000')
    with open(prototxt, 'w') as configfile:
        cp.write(configfile)
    subprocess.call(['sed', '-i', '/asection/d', prototxt])
    subprocess.call(['sed', '-i', 's/=/:/g', prototxt])

    outputFile = 'output_walker.txt'
    try:
        os.remove(outputFile)
    except:
        pass
    accuracy_dictionary = {}
    key_varying_definition = {
                "scale":  [0.00190625, 0.00290625, 0.00390625, 00.00490625, 0.00590625] ,
                "batch_size": [2, 4, 8, 16, 32, 64 ],
                "conv1_kernel_size": [3, 4, 5, 6, 7],
                "conv1_stride": [1, 2, 3],
                "pool1_kernel_size": [1, 2, 3, 4],
                "pool1_stride": [1, 2, 3, 4],
                "conv2_kernel_size": [3, 4, 5, 6, 7],
                "conv2_stride": [1,2, 4, 5],
                "pool2_kernel_size": [1, 2, 4, 5],
                "pool2_stride": [1, 2, 3, 4],
                "conv3_kernel_size": [1,2,3,4],
                "conv3_stride": [1,2,3,4]
            }
    for key in [
                "conv1_kernel_size",
                "conv1_stride",
                "pool1_kernel_size",
                "pool1_stride",
                "conv2_kernel_size",
                "conv2_stride",
                "pool2_kernel_size",
                "pool2_stride",
                "scale",
                "batch_size",
                "conv3_kernel_size",
                "conv3_stride",
            ]:
            context = {
                "prob": "prob_name",
                "ip1_name": "ip1",
                "relu1_name": "relu1",
                "ip2_name": "ip2",
                "accuracy_name": "accuracy",
                "loss_name":"loss",
                "script_name": "script", 
                "mnist_name": "mnist", 
                "conv1_name": "conv1",
                "pool1_name": "pool1",
                "conv2_name": "conv2",
                "pool2_name": "pool2",
                "scale":  0.00390625,
                "batch_size": 16,
                "conv1_kernel_size": 5,
                "conv1_stride": 1,
                "pool1_kernel_size": 2, 
                "pool1_stride": 2,
                "conv2_kernel_size": 5,  
                "conv2_stride": 1,
                "pool2_kernel_size": 2, 
                "pool2_stride": 2,
                "conv3_kernel_size": 1,  
                "conv3_stride": 1,
            }
            accuracy_array = []
            for value in key_varying_definition[key]:
                context[key]=value
                context["prob"] = context["prob"] + "0"
                context["ip1_name"] = context["ip1_name"] + "0"
                context["relu1_name"] = context["relu1_name"] + "0"
                context["ip2_name"] = context["ip2_name"] + "0"
                context["accuracy_name"] = context["accuracy_name"] + "0"
                context["loss_name"] = context["loss_name"] + "0"
                context["script_name"] = context["script_name"] + "0"
                context["mnist_name"] = context["mnist_name"] + "0"
                context["conv1_name"] = context["conv1_name"] + "0"
                context["pool1_name"] = context["pool1_name"] + "0"
                context["conv2_name"] = context["conv2_name"] + "0"
                context["pool2_name"] = context["pool2_name"] + "0"
                config = render('trainer_template.txt', context)
                lenetPath = '/home/paolo/caffe/dummy/models/lenet_train_val.prototxt'
                with open (lenetPath, 'w') as lenetFile:
                    lenetFile.write(config)
                config = render('deploy_template.txt', context)
                lenetPath = '/home/paolo/caffe/dummy/models/lenet_deploy.prototxt'
                with open (lenetPath, 'w') as lenetFile:
                    lenetFile.write(config)
                print "train..."
                subprocess.call('./train_dummy_net.sh')
                print "test..."
                output = subprocess.Popen('./test_dummy_net.sh', stdout=subprocess.PIPE)
                accuracy = output.stdout.readline()
                accuracy_array.append(float(accuracy))

                with open(outputFile, 'a') as txt:
                    txt.write(str(key) + ": " + str(value) + "\n")
                    while True:
                      line = output.stdout.readline()
                      if line != '':
                        txt.write(line)
                      else:
                        break
                    accuracy_dictionary[key]=accuracy_array
            attributeArray = key_varying_definition[key]
            xstart = attributeArray[0]
            xend = attributeArray[len(attributeArray) - 1]
            array = numpy.array(accuracy_array)
            ystart = min(accuracy_array)
            yend = max(accuracy_array)
            fig = plt.figure()
            plt.plot(accuracy_array, color="blue")
            plt.title("")
            plt.xlabel('Variavel alterada: %s'%(str(key)))
            plt.axis([xstart, xend, ystart, yend])
            plt.ylabel('Taxa de acerto (%)')
            plt.legend()
            plt.savefig(str(key) + "_plot.pdf")
            plt.close()
        
    with open(outputFile, 'a') as txt:
        txt.write("\\begin{figure}[H]")
        txt.write("\\centerline{")
        txt.write("\\includegraphics[scale=0.6]{%s_plot.pdf}"%str(key))
        txt.write("{\\end{figure}")
        txt.write(pprint.pformat(accuracy_dictionary))


if __name__ == "__main__":
    main()
