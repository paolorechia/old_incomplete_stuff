#include <iostream>
using namespace std;

int main()
{
    int fibn, fibn1, fibn2, n;
    cout<<"20 primeiros numeros da sequencia de Fibonnaci:"<<endl;
    n=0;
    while (n<30)
    {
        if (n==0)
        {
            fibn=0;
            fibn2=0;
            cout<<fibn;
        }
        else if (n==1)
        {
            fibn=1;
            fibn1=1;
            cout<<fibn;
        }
        else if (n>1)
        {
            fibn=fibn1+fibn2;
            cout<<fibn;
            fibn2=fibn1;
            fibn1=fibn;
        }
        cout<<",";
        n=n+1;
    }
    cout<<endl;
}

