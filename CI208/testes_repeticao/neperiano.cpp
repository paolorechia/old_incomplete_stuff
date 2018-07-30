#include <iostream>

using namespace std;

int fat (int n)
{
    int fat;

    fat = 1;

    while (n != 0)
    {
        fat = fat * n;
        n = n - 1;
    }

    return fat;
}

int main()
{
    int i;
    float e;

    i = 0;
    e = 0.0;

    while (i < 10)
    {
        e = e + 1.0 / fat(i);
        i = i + 1;
    }

    cout << "e = " << e << endl << endl;

}
