#include <iostream>
using namespace std;

int main()
{
    int x, denominador, i30, id;
    cout<<"Os 30 primeiros numeros primos:"<<endl;
    i30=0;
    x=1;
    while (i30<30)
    {
        if (x<=2)
        {
            i30=i30+1;
            cout<<x<<" ";
            x=x+1;
        }
        else
        {
            id=0;
            denominador=2;
            while (denominador<x)
            {
                if (x%denominador!=0)
                    id=id+1;
                denominador=denominador+1;
                }
            if (id==(x-2)) //Desconsidera 1 e o proprio x
            {
                cout<<x<<" ";
                i30=i30+1;
            }
            x=x+1;
        }
    }
    cout<<endl;
}

