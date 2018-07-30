#include <iostream>
using namespace std;

int main()
{
    int x, produto;
    produto=1;
    x=1;
    while (x<=12)
    {
        produto=produto*x;
        x=x+2;
    }
    cout<<"Produto dos numeros impares de 1 a 12= "<<produto<<endl;
}
