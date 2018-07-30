#include <iostream>
using namespace std;

int main()
{
    float x, media, i;
    cout<<"Entre com uma sequencia de dados: "<<endl;
    media=0;
    i=0;
    x=10; //valor diferente de zero para entrar no loop
    while (x!=0)
    {
        cin>>x;
        if (x!=0) //O zero nao deve ser considerado no calculo da media
        {
            media=media+x;
            i=i+1;
        }
    }
    media=media/i;  //(soma dos dados)/(numero de dados)
    cout<<endl<<"Media aritmetica= "<<media<<endl;
}
