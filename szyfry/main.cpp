#include<iostream>
#include <math.h>

using namespace std;

int main() {
    FILE *we, *wy;
    char znak;       //znak odczytany z pliku
//Przed uruchomieniem programu nalezy utworzyc 2 pliki - 1. z tekstem jawnym, 2. pusty na t.zaszyfrowany
    char plik_jawny[20];  //nazwa pliku z tekstem jawnym
    char plik_zaszyfrowany[20];  //nazwa pliku z tekstem zaszyfrownym
    cout << "Podaj nazwe pliku, ktorego tresc ma zostac zaszyfrowana: ";
    cin >> plik_jawny;
    cout << "Podaj nazwe pliku wynikowego: ";
    cin >> plik_zaszyfrowany;
    if ((we = fopen(plik_jawny, "rb")) != NULL)    //otwieranie pliku 1. do odczytu - oba pliki musza istniec
    {
        if ((wy = fopen(plik_zaszyfrowany, "wb")) != NULL)  //otwieranie pliku 2. do zapisu
        {
            while (//dopoki nie skoncza sie znaki w zdaniu / pliku)
            {
                if ((znak >= 'A') && (znak <= 'Z')) {
                    znak -= 'A';
                    znak += 13;
                    znak = znak%26;
                    znak += 'A';
                    putc(znak, wy);
                } else if ((znak >= 'a') && (znak <= 'z')) {
                    znak -= 'a';
                    znak += 13;
                    znak = znak%26;
                    znak += 'a';
                    putc(znak, wy);
                } else if ((znak >= '0') && (znak <= '9')) {
                    znak -= '0';
                    znak += 13;
                    znak = znak%10;
                    znak += '0';
                    putc(znak, wy); //wczytanie do pliku
                }
//Wszystkie inne znaki sa pomijane. Jezeli zalezy Ci aby nie pomijac niektorych znakow powinienes
//dodac w tym miejscu nastepujace linijki kodu:
//else if(znak==nr)   gdzie przez nr rozumiemy nr kodu ASCII danego znaku
//{znak+=13;
//putc(znak,wy);}
//W funkcji deszyfrujacej nalezy umiescic to samo zmieniajac + na -.
            }
            fclose(wy);
        }
        fclose(we);
    }
    cout << "Szyfrowanie zostalo zakonczone";
    return 1;
}