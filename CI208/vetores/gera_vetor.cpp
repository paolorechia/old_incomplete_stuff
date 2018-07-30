#include <iostream>
#include <string>

#define N_PARAMETROS 1

using namespace std;

int main(int argc, char * argv[]){
    if (argc != N_PARAMETROS + 1){
        cout << "Usage: ./" << argv[0] << "[tamanho_vetor]" <<endl;
        return -1;
    }
    int n;
    n = std::stoi(argv[1]); 
    int vetor[n];
    for (int i = 0; i < n; i++){
        cout << vetor[i] << cout " ";
    }
    cout << endl;
    return 0;
}
