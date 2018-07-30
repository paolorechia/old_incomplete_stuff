#include <iostream>
using namespace std;

int main()
{
    int x, aux;
    cout<<"Entre com um inteiro: ";
    cin>>x;
    cout<<endl<<x<<"! = ";
    aux=x-1;
    while (aux>0)
    {
        x=x*aux;
        aux=aux-1;
    }
    cout<<x<<endl;
}

