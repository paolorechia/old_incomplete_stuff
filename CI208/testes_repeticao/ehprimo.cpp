#include <iostream>
using namespace std;

int main()
{
    int x, aux, i;
    x=0; //Inteiro menor que 1 para entrar no loop
    while (x<=1) //checa se x eh um inteiro maior que 1
    {
        cout<<"Entre com um inteiro maior que 1: ";
        cin>>x;
        if (x<=1)
            cout<<"Numero invalido"<<endl;
    }
    i=0;
    aux=2;
    while (aux<x)
    {
        if (x%aux==0)
            i=i+1;
        aux=aux+1;
    }
    if (i==0)
        cout<<endl<<x<<" eh primo."<<endl;
    else
        cout<<endl<<x<<" nao eh primo."<<endl;
}


