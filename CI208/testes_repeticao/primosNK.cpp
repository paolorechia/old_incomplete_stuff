#include <iostream>
using namespace std;

int main()
{
    int N, K, x, denominador, i, soma;
    cout<<"PROGRAMA QUE CALCULA A SOMA DOS NUMEROS PRIMOS DO INTERVALO ENTRE ‘N’ E ‘K’"<<endl<<endl<<"Entre com N: ";
    cin>>N;
    cout<<"Entre com K: ";
    cin>>K;
    cout<<endl;
    if (N>K)
    {
        x=N;
        N=K;
        K=x;
    }
    soma=0;
    x=N;
    while (x<=K)
    {
        if (x<=2)
            soma=soma+x;
        else
        {
            i=0;
            denominador=2; //desconsidera 1
            while (denominador<x) //"<": desconsidera x
            {
                if (x%denominador!=0)
                    i=i+1;
                denominador=denominador+1;
            }
            if (i==(x-2)) //Desconsidera 1 e o proprio x
                soma=soma+x;
        }
        x=x+1;
    }
    cout<<"Soma= "<<soma<<endl;
}

