#include <iostream>
#include "basic_op.h"

#define N 7

using namespace std;

void trocaelems(int * vetor, int tam){
    int i, j, aux;
    i = 0;
    j = tam - 1; 
    while (i < tam/2){
        aux = vetor[i];
        vetor[i]= vetor[j];
        vetor[j]=aux;                
        i++;
        j--;
    }
}
/*
void imprime_vetor(int * vetor, int tam){
    int i;
    for (i = 0; i < tam ; i++){
        cout << vetor[i] << " ";         
    }
    cout << endl;
}
*/

int main(){
    
    int vetor [N] = {1, 2, 3, 4, 5, 6, 7};
    trocaelems(vetor, N);
    imprime_vetor(vetor, N);
    
    return 0;
}
