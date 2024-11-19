#include <iostream>
#include <fstream>
using namespace std;

int nwd(int liczba1, int liczba2)
{
    while (liczba1 > 0)
    {
        liczba1 = liczba1%liczba2;
        liczba2 = liczba2-liczba1;
    }
    return liczba2;
}

int main()
{
    int liczba1, liczba2, liczba3;
    int najmniejsza = 1; //--> jaka domyslna wartosc
    int ile = 0;

    fstream odczyt ("liczby_nwd.txt",ios::in);
    fstream wypisz ("wyniki3.txt",ios::out);

    //sprostowanie jaka domyslna --> pytanie jak liczymy pierwszy wiersz
    odczyt >> liczba1 >> liczba2 >> liczba3;
    najmniejsza = nwd(nwd(liczba1, liczba2),liczba3);
    wypisz <<"nwd: " << nwd(nwd(liczba1, liczba2),liczba3) << endl;
    //ile++;

    for(int i=0;i<999;i++)
    {
        //int nwd_wynik = nwd(nwd(liczba1, liczba2),liczba3);
        wypisz <<"nwd: " << nwd(nwd(liczba1, liczba2),liczba3) << endl;
        if (najmniejsza > nwd(nwd(liczba1, liczba2),liczba3))
        {
            najmniejsza = nwd(nwd(liczba1, liczba2),liczba3);
        }else if (nwd(nwd(liczba1, liczba2),liczba3) == najmniejsza)
        {
            ile++;
        }

    }
    cout << "Najmniejsze nwd wiersza: "<<najmniejsza<<endl;
    cout << "Wystopilo "<<ile<<" razy"<<endl;
    return 0;
}