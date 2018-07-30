#include <iostream>
using namespace std;

int main()
{
    float S, numerador, denominador;
    int N, i;
    cout<<"Entre com o inteiro N: ";
    cin>>N;
    S=0;
    numerador=5;
    denominador=2;
    i=N;
    while (i>0)
    {
        S=S+numerador/denominador;
        numerador=numerador*5;
        denominador=denominador+2;
        i=i-1;
    }
    cout<<"S= "<<S<<endl;
}
