#include <iostream>

#define N 100

using namespace std;

float media_salarial(float vetor[], int tam){
    int i = 0;
    float soma = 0;
    while (i < tam){
        soma = soma + vetor[i];
        i++;
    }
    return (soma/tam);
}

int maior_idade(int vetor[], int tam){
    int i = 0;
    int maior = -999999;
    while (i < tam){
        if (vetor[i] > maior){
            maior = vetor[i];
        }
        i++;
    }
    return maior;
}
int menor_idade(int vetor[], int tam){
    int i = 0;
    int menor = 999999;
    while (i < tam){
        if (vetor[i] < menor){
            menor = vetor[i];
        }
        i++;
    }
    return menor;
}

int media_idade(int vetor[], int tam){
    int i = 0;
    int soma = 0;
    while (i < tam){
        soma = soma + vetor[i];
        i++;
    }
    return (soma/tam);
}

// quantidade de mulheres com 3 filhos e que recebem ateh 500,00 reais
int qtde_mulheres(char sexo[], float salario[], int filhos[], int tam){
    int i = 0;
    int quantidade = 0;
    while (i < tam){
        if ((sexo[i] == 'M') &&
           (filhos[i] == 3)  &&
           (salario[i] < 300)){
                quantidade++;  
        }
        i++;
    }
    return quantidade;
}

int main(){
    int idade[N]; 
    char sexo[N];
    int num_filhos[N];
    float salario[N];

    int i = -1;
    idade[0] = -1;
    do {
        i++;
        cout << "Habitante " << i << ": "    << endl;
        cout << "Entre com idade           : ";
        cin  >> idade[i];
        cout << endl;

        if (idade[i] == 0){
            break;
        }

        cout << "Entre com sexo (M/F)      : ";
        cin  >> sexo[i];
        cout << endl;

        cout << "Entre com numero de filhos: ";
        cin  >> num_filhos[i];
        cout << endl;

        cout << "Entre com salario         : ";
        cin  >> salario[i];
        cout << endl;
    } while (idade[i] != 0 && i < N);

    cout << "Media salarial: " <<  media_salarial(salario, i) << endl;
    cout << "Maior idade   : " <<  maior_idade(idade, i)      << endl;
    cout << "Menor idade   : " <<  menor_idade(idade, i)      << endl;
    cout << "Idade media   : " <<  media_idade(idade, i)      << endl;
    cout << "Mulheres 3f500: ";
    cout << qtde_mulheres(sexo, salario, num_filhos, i) << endl;

    return 0;
}
