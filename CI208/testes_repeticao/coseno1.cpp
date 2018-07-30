
#include <iostream>
using namespace std;

int main()
{
    float S;
    int i, fat, ifat;
    S=1;
    i=2;
    while (i<=13) //A primeira parcela (1) ja foi considerada
    {
        fat=(i-1)*2;
        ifat=fat-1;
        while (ifat>0)
        {
            fat=fat*ifat;
            ifat=ifat-1;
        }
        if (i%2==0)
            S=S-1.0/fat; //Use 1.0 ou declare float fat
        else
            S=S+1.0/fat; //Use 1.0 ou declare float fat
        i=i+1;
    }
    cout<<"cos (1 radiano) = "<<S<<endl;
}
