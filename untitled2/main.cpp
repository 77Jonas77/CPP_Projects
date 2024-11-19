#include <iostream>
#include <cmath>
#include <algorithm>
using std::cout;
using std::cin;
using std::endl;

double BMI(double h, double w){
    return w/pow(h,2);
}

//void show(int max, int a, int b, int c){
//    for(int i=max;i>0;i--) {
//        cout << (a >= i ? "*" : " ");
//        cout << (b >= i ? "*" : " ");
//        cout << (c >= i ? "*" : " ");
//        cout << endl;
//    }
//}

int main() {
    //zadanie1
    /*double height, weight;
    cout << "Podaj wzrost: ";
    cin >> height;
    cout << "Podaj wage: ";
    cin >> weight;
    cout << BMI(height,weight) << endl;*/

    //zadanie2
    //show(8,7,4,5);

    //zadanie3
    /*int l = 1;
    int maxs = 0, maxl;
    do{
        cout << "podaj liczbe (0 jesli koniec): ";
        int suma=0;
        cin >> l;
        int l1 = l;
        while(l1!=0){
            suma += l1%10;
            l1/=10;
        }
        if(suma>maxs){
            maxs = suma;
            maxl = l;
        }
        cout << endl;
    }while(l!=0);
    cout << "max suma: " << maxs << " dla liczby: " << maxl;*/

    //zadanie4
    /*int max = 1000000;
    int min = 1;
    */

    int min = 1;
    int max = 1000000;

    for(int i=0;i<20;i++){
        int half = (min + max)/2;
        cout << "Czy jest to " << half << "?" << endl;
        char input;
        cin >> input;
        switch (input) {
            case 's':
                max = half;
                break;
            case 'b':
                min = half;
                break;
            case 'y':
                cout << "haha wygralem" << endl;
                i=20;
        }
    }

/*
    for(int i=0;i<20;i++){
        int half = (min+max)/2;
        cout << i+1 <<"." << " Czy jest to liczba: " << half << "?" << endl;
        char input;
        cin >> input;
        switch(input){
            case 's':
                max = half;
                break;
            case 'b':
                min = half;
                break;
            case 'y':
                cout << "hehe wygralem, pomyslana liczba to: " << half;
        }
    }
     */

    return 0;
}
