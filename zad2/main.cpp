#include <iostream>
#include <fstream>

using namespace std;

string deszyfruj(string slowo, string klucz) {
    int licznik = 0, literasz;
    char litera;
    string szyfr = "";

    for (int i = 0; i < slowo.size(); i++) {
        literasz = slowo[i] - klucz[licznik] + 64;

        while (literasz < 65)
            literasz += 26;

        if (licznik == klucz.size() - 1)
            licznik = 0;
        else
            licznik++;

        litera = literasz;
        szyfr = szyfr + litera;
    }
    return szyfr;
}

int main() {
    fstream plik_dane1, plik_dane2, plik_zapis;
    string napis, klucz, szyfr;
    int licznik = 0, dl_max = 0;

    plik_dane1.open("sz.txt", ios::in);
    plik_dane2.open("klucze2.txt", ios::in);
    plik_zapis.open("wynik4b.txt", ios::out);

    plik_zapis << "Zadanie 2" << endl;

    if (plik_dane1.good())
        while (!plik_dane1.eof()) {
            plik_dane1 >> napis;
            plik_dane2 >> klucz;

            szyfr = deszyfruj(napis, klucz);
            cout << szyfr << endl;
            plik_zapis << szyfr << endl;

        }
    plik_dane1.close();
    plik_dane2.close();

    plik_zapis.close();

    return 0;
}