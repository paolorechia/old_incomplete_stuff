#include <iostream>

using namespace std;

#define N 20

void soma_vetores(int * entrada1, int * entrada2, int * saida, int tam){
    int i;
    for (i = 0; i < tam ; i++){
        saida[i] += entrada1[i] + entrada2[i];
    }
}
void le_vetor(int *vetor, int tam){
    int i;
    for (i = 0; i < tam ; i++){
        cin >> vetor[i];
    }
}

void imprime_vetor(int * vetor, int tam){
    int i;
    for (i = 0; i < tam ; i++){
        cout << vetor[i] << " ";         
    }
    cout << endl;
}


int main(){
    int vetor[N];
    int vetor2[N];
    int soma[N];
    cout << "Entre com vetor 1:" << endl;
    le_vetor(vetor, N); 
    cout << "Entre com vetor 2:" << endl;
    le_vetor(vetor2, N); 
    cout << "O vetor de somas é:" << endl;
    soma_vetores(vetor, vetor2, soma, N);
    imprime_vetor(vetor, N);
    return 0;
}
