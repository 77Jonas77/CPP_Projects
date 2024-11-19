#include <iostream>
using namespace std;

int main(){
    //tytul programucout << "Kalkulator" << endl << endl;

    //deklaracj zmiennych
    float liczba1, liczba2;
    char znak;

    //odebranie wartosci zmiennej
    cout << "Podaj pierwsza liczbe" << endl;
    cin >> liczba1;
    cout << "Podaj znak dzialania" << endl;
    cin >> znak;
    cout << "Podaj druga liczbe" << endl;
    cin >> liczba2;

    //wykonanie obliczen dla odpowiedniego znaku dzialania
    switch (znak){
        case '+':
            cout << endl << "Wynik dzialania: " << liczba1 << znak << liczba2 << '=';
            cout << liczba1+liczba2;
            break;
        case '-':
            cout << endl << "Wynik dzialania: " << liczba1 << znak << liczba2 << '=';
            cout << liczba1-liczba2;
            break;
        case '*':
            cout << endl << "Wynik dzialania: " << liczba1 << znak << liczba2 << '=';
            cout << liczba1*liczba2;
            break;
        case '/':
            cout << endl << "Wynik dzialania: " << liczba1 << znak << liczba2 << '=';
            cout << liczba1/liczba2;
            break;
        default:
            cout << endl << "Nie znam wprowadzonego znaku dzialania :(" << endl;
            break;
    }

    if(znak=='+'){
        cout << endl << "Wynik dzialania: " << liczba1 << znak << liczba2 << '=';
        cout << liczba1+liczba2;
    }else if(znak=='-'){

    }

    return 0;
}