#include <iostream>
using namespace std;

int main() {
    int liczba_spr;
    cin >> liczba_spr;

    bool czy_zlozona=false;

    for(int i=2; i<liczba_spr; i++){

        if(czy_zlozona==false && liczba_spr%i==0)
        {
            czy_zlozona=true;
        }
    }
    if(czy_zlozona==true){
        cout<<"zlozona";
    }
    if(czy_zlozona==false){
        cout<<"pierwsza";
    }

    return 0;
}