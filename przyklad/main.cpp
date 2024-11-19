#include <iostream>
#include <algorithm>
#include <fstream>
#include <cmath>

using namespace std;

int szesc_na_dzies(string slowo) {
    int suma = 0;
    int licznik = 0;
    for (int i = slowo.size() - 1; i >= 0; i--) {
        int wartosc;
        if ((slowo[i] <= '9') && (slowo[i] >= '0')) {
            wartosc = slowo[i] - '0';
        } else {
            wartosc = slowo[i] - 'A' + 10;
        }
        suma += pow(16, licznik) * wartosc;
        licznik += 1;
    }
    return suma;
}

int main() {
    string slowa[1000];
    fstream plik_wczyt, plik_zapisz;
    plik_wczyt.open("/Users/jonaszsojka/CLionProjects/przyklad/dane_1.txt", ios::in);
    plik_zapisz.open("zapisz_2.txt", ios::out);

    for (int i = 0; i < 1000 && !plik_wczyt.eof(); i++) {
        plik_wczyt >> slowa[i];
    }

    for (int i = 0; i < 1000; i++) {
        int liczba = szesc_na_dzies(slowa[i]);
        if (liczba % 2 == 0) {
            cout << liczba << endl;
        }
    }

    plik_wczyt.close();
    plik_zapisz.close();

    return 0;
}
