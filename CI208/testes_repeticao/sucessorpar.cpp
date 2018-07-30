#include <iostream>
using namespace std;

int main()
{
    int x;
    cout<<"Entre com uma sequencia de numeros pares, sendo zero a ordem de parada."<<endl;
    x=2; //valor diferente de zero para o programa iniciar no loop
    while (x>0)
    {
        cin>>x;
        if (x!=0 && x%2==0) //Zero nao deve ser considerado no calculo
                            //Checa se o numero eh par
        {
            cout<<x+2<<" eh seu sucessor"<<endl<<endl;
        }
        if (x%2!=0)
            cout<<"Esse numero nao eh par"<<endl<<endl;
    }
}

