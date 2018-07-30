#include <iostream>

#define N 10

using namespace std;

int imprime_matriz(int matriz[N][N]){
    for (int i = 0; i < N ; i++){
        for (int j = 0; j < N; j++){
            cout << matriz[i][j] << "\t";
        }
        cout <<endl;
    }
}

int trocaelems(int matriz[N][N]){
    int i, j, maior, aux;
    i = 0;
    while (i < N){
        j = 0;
        maior = 0;
        while (j < N){
            if (matriz[i][j] > matriz[i][maior])
            maior = j;
            j++;
        }
        aux = matriz[i][0];
        matriz[i][0]=matriz[i][maior];
        matriz[i][maior]=aux;
        i++;
    }
}


int main(){
    int matriz[N][N];
    cout << "Entre com uma matriz 10x10 (100 numeros)" << endl;
    int i = 0;
    int j;
    while (i < N){
        j = 0;
        while (j < N){
            cin >> matriz[i][j];
            j++;
        }
        i++;
    }
    imprime_matriz(matriz);
    cout << endl;
    cout << endl;
    trocaelems(matriz);
    imprime_matriz(matriz);
    return 0;
}
