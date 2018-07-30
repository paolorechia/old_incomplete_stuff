#include <iostream>

#define N 3
#define M 3

using namespace std;

int imprime_matriz(int matriz[][M]){
    for (int i = 0; i < N ; i++){
        for (int j = 0; j < M; j++){
            cout << matriz[i][j] << "\t";
        }
        cout <<endl;
    }
}

int soma_matrizes(int A[][M], int B[][M], int C[][M]){
    for (int i = 0; i < N ; i++){
        for (int j = 0; j < M; j++){
            C[i][j] = A[i][j] + B[i][j];
        }
        cout <<endl;
    }
    return 0;
}


int main(){
    int A[N][M]  = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    int B[N][M] = {3, 5, 7, 9, 11, 13, 15, 17, 19};
    int C[N][M];
    cout << "Matriz A:" << endl;;
    imprime_matriz(A);
    cout << "Matriz B:" << endl;
    imprime_matriz(B);
    soma_matrizes(A, B, C);
    cout << "A + B = C:" <<endl;
    imprime_matriz(C);
    return 0;
}
