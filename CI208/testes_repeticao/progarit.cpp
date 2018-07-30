#include <iostream>

using namespace std;

int main()
{
    int S, i, x;

    S = 0;
    cin >> x;
    i = 1;


    while(i <= 20)
    {
        S = S + x;
        x = x + 3;
        i = i + 1;
    }

    cout << "SOMA = " << S << endl;

}

