#include <iostream>
using namespace std;

int main()
{
    int x, maior;
    cout<<"Entre com uma sequencia de inteiros positivos, sendo zero a ordem de parada"<<endl;
    maior=0; //O zero eh menor que o menor valor permitido da sequencia
    x=18; //valor diferente de zero para o programa entrar no loop
    while (x!=0)
    {
        cin>>x;
        if (x!=0 && x>0) //Zero nao deve ser considerado na busca do maior valor
                        //Verifica se x eh positivo
        {
            if (x>maior)
                maior=x;
        }
        if (x<0)
            cout<<"Numero invalido"<<endl;
    }
    cout<<endl<<endl<<"Maior: "<<maior<<endl;
}
