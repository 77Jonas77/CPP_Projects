#include <iostream>
#include <fstream> //bibl dla pliku
#include <string>  //bibl dla ciagu znakow / typ zmiennej / tablica
using namespace std;

int main()
{
    string slowo, najdluzsze;
    fstream plik;

    plik.open("przykladowy_plik.txt", ios::in); //ios::in mowi nam ze inputoutputstream na tryb wczytywania
    for(int i=0;i<10;i++){ //podawane mamy 10 linii w pliku -> inf. z polecenia
        plik >> slowo; //wczytujemy z pliku te slowa po kolei (1 za kazdym obrotem petli)
        if(najdluzsze.size()<slowo.size()) //jesli dlugosc slowa ktore wczyt. jest wieksza od dotychcz. najw, to teraz najw. jest slowo wczytane
            najdluzsze = slowo; //wiec piszemy ze najdl. teraz jest slowo
    }
    plik.close();
    cout << "najdluzsze slowo z posrod wczytanych to: " << najdluzsze << endl;

    return 0; //to piszesz zawsze tak o
}