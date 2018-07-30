#include <iostream>
using namespace std;

int main()
{
    int x, soma;
    cout<<"Entre com uma sequencia de numeros inteiros, sendo 0 a ordem de parada:"<<endl;
    soma=0;
    x=10; //numero diferente de zero para iniciar o loop
    while (x!=0)
    {
        cin>>x;
        soma=soma+x; //se o usuario entrar com zero, a soma nao se altera
    }
    cout<<endl<<"Soma total= "<<soma<<endl;
}
