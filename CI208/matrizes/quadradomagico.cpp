#include <iostream>
#define N 3
#define M 3

using namespace std;

bool quadradomagico(int matriz[N][M]){
    int i, j;

    i = 0;

    int soma1 = 0;
    int soma2 = 0;

    // soma primeira linha
    for (j = 0; j< M; j++){
        soma1 += matriz[i][j];
    }

    // confere com soma das outras linhas
    for (i = 1; i < N; i++){
        soma2 = 0;
        for (j = 0; j < M; j++){
            soma2 += matriz[i][j];
        }
        if (soma1 != soma2){
            return false;
        }
    }
    // confere soma das colunas
    for (i=0; i < N; i++){
        soma2 = 0;
        for (j = 0; j< M; j++){
            soma2+= matriz[j][i];
        }
        if (soma1 != soma2){
            return false;
        }
    }
    // confere diagonal principal
    soma2 = 0;
    for (i=0; i < N; i++){
        soma2+= matriz[i][i];
    }
    if (soma1 != soma2){
        return false;
    }

    // confere diagonal secundaria
    soma2 = 0;
    for (i=0; i < N; i++){
        soma2+= matriz[i][N - i - 1];
    }
    if (soma1 != soma2){
        cout << soma2 << endl;
        return false;
    }

    // se todas as somas forem iguais, chegou aqui
    // logo, eh uma quadrado magico
    return true;
}

int main(){
    int matriz[N][M]= {8, 0, 7, 4, 5, 6, 3, 10, 2};
    int matriz2[N][M]={9, 0, 7, 3, 5, 6, 3, 10, 2};
    if(quadradomagico(matriz)){
        cout << "Matriz 1 eh um quadrado magico" << endl;
    }
    else{
        cout << "Matriz 1 nao eh um quadrado magico" << endl;
;
    }
    if(quadradomagico(matriz2)){
        cout << "Matriz 2 eh um quadrado magico" << endl;
;
    }
    else{
        cout << "Matriz 2 nao eh um quadrado magico" << endl;
;
    }
    return 0;
}
