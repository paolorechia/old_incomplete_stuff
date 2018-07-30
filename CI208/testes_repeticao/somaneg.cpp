#include <iostream>
using namespace std;

int main()
{
    int x, soma;
    cout<<"Entre com uma sequencia de numeros inteiros, sendo um numero negativo a ordem de parada:"<<endl;
    soma=0;
    x=3; //valor positivo para o programa entrar no loop
    while (x>0)
    {
        cin>>x;
        if (x>0)
            soma=soma+x;
    }
    cout<<endl<<"Soma= "<<soma<<endl;
}

