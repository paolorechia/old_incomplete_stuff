#include <iostream>

#define N 7

using namespace std;

int imprime_pasc(int matriz[N][N]){
    for (int i = 0; i < N ; i++){
        for (int j = 0; j <= i; j++){
            cout << matriz[i][j] << "\t";
        }
        cout <<endl;
    }
}

int gerapascal(int matriz[N][N]){
    // inicializa primeiros elementos da matriz
    matriz[0][0] = 1;
    matriz[1][0] = 1;
    matriz[1][1] = 1;
    int i = 2;
    while (i < N){
        int j = 0;
        while (j <= i){
            if (j == 0){
                matriz[i][j]=matriz[i-1][j];
            }
            else if (j == i){
                matriz[i][j]=matriz[i-1][j-1];
            }
            else
                matriz[i][j]=matriz[i-1][j-1] + matriz[i-1][j];
            j++;
        }
        i++;
    }
}

int main(){
    int matriz[N][N];
    gerapascal(matriz);
    imprime_pasc(matriz);
    return 0;
}
