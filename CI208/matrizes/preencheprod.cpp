#include <iostream>

#define N 9
#define M 15

using namespace std;

int imprime_matriz(int matriz[N][M]){
    for (int i = 0; i < N ; i++){
        for (int j = 0; j < N; j++){
            cout << matriz[i][j] << "\t";
        }
        cout <<endl;
    }
}


int main(){
    int matriz[N][M];
    int i, j;
    i = 0;
    while (i < N){
        j = 0;
        while (j < N){
            matriz[i][j]=i*j;
            j++;
        }
        i++;
    }
    imprime_matriz(matriz);
    cout << endl;
    return 0;
}
