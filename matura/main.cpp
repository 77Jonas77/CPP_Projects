#include <iostream>
using namespace std;

int maks(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

int main()
{
    int n;
    cin >> n;
    int tab[n];
    for(int i=0; i<n; i++)
    {
        cin >> tab[i];
    }
    int rezultat = tab[0];
    for(int i=1; i<n; i++)
    {
        rezultat = NWD(rezultat,tab[i]);
    }
    cout<<"NWD to:"<<rezultat<<endl;

    return 0;
}