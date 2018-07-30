#include <iostream>
using namespace std;

int main()
{
    int x, tam, comparacao, ip, alg1, alg2, i, aux;
    cout<<"Entre com um inteiro positivo: ";
    cin>>x;
    while (x<10) //enquanto x tem apenas 1 digito
    {
        cout<<"Numero invalido. Digite um inteiro positivo COM MAIS DE UM DIGITO: ";
        cin>>x;
    }
    tam=1;
    aux=x;
    while (aux>=10)
    {
        aux=aux/10;
        tam=tam+1;
    }
    ip=0;
    comparacao=1;
    while (comparacao<=(tam/2))
    {
        alg1=x;
        i=1;
        while (i<comparacao)
        {
            alg1=alg1/10;
            i=i+1;
        }
        alg1=alg1%10;
        alg2=x;
        i=1;
        while (i<(tam-(comparacao-1)))
        {
            alg2=alg2/10;
            i=i+1;
        }
        alg2=alg2%10;
        if (alg1==alg2)
            ip=ip+1;
        comparacao=comparacao+1;
    }
    cout<<endl<<x;
    if (ip==(tam/2))
        cout<<" eh palindromo"<<endl;
    else
        cout<<" nao eh palindromo"<<endl;
}


