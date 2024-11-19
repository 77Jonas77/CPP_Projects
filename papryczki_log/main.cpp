#include <iostream>
using namespace std;

int main() {
    //wprowadzenie 1 wiersza
    int k;
    cin>>k;

    //wypelnienie tablicy potegami
    int tab[k+1];
    int powr=1;

    for(int i=0; i<=k;i++){
        tab[i]=powr;
        powr*=2;
    }

    //wypelnienie tablicy stanem
    int stan[k+1];

    for(int j=0;j<=k;j++){
        cin>>stan[j];
    }

    int sum=0;
    bool y = true;

    //wiemy, ze jesli z dotychczasowej sumy nie jestesmy w stanie osiagnac nastepnej potegi 2, to
    //sum+1, daje nam liczbe, ktorej nie bedziemy w stanie osiagnac jako 1
    for(int i =0; i<k;i++){
        sum+=tab[i]*stan[i];

        if (sum<tab[i+1]-1){
            cout<<sum+1;
            y=false;
            break;
        }
    }

    if(y){
        cout<<sum+tab[k]*stan[k]+1;
    }

    return 0;
}