#include <iostream>
#define SENHA 1234
using namespace std;

int main()
{
    int x;
    x=SENHA-2; //Valor diferente de SENHA para entrar no loop
    while (x!=SENHA)
    {
        cout<<"Senha: ";
        cin>>x;
        if (x!=SENHA)
            cout<<"Senha incorreta!"<<endl<<endl;
    }
    cout<<endl<<endl<<"Bem vindo"<<endl;
}
