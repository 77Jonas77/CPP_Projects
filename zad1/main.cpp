#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int main() {
    string tab[200];
    sort(tab,tab+200);
//    string t_s[200][320];
//    int ile_wierszy = 0, wiersze_s = 0;
//
//    fstream plo;
//    plo.open("/Users/jonaszsojka/CLionProjects/zad1/dane.txt", ios::in);
//
//    if (!plo) {
//        cout << "Nie mozna otworzyc pliku.";
//        return 1;
//    }
//
//    for (int i = 0; i < 200; i++) {
//        for (int j = 0; j < 320; j++) {
//            if (!(plo >> t_s[i][j])) {
//                break;
//            }
//            cout << t_s[i][j] << endl;
//        }
//        if (plo.fail()) {
//            break;
//        }
//    }
    string t_s[200][320];
    string wczytywana;
    int t[200][320], ile_wierszy = 0, wiersze_s = 0;
    fstream plo;
    plo.open("/Users/jonaszsojka/CLionProjects/zad1/dane.txt", ios::in);
    for (int i = 0; i < 200; i++) {
        for (int j = 0; j < 320; j++) {
            //        plo>>t[i][j];
            plo >> wczytywana;
            t_s[i][j] = wczytywana;
            // plo>>t_s[i][j];
            cout << t_s[i][j] << endl;
        }
        if (plo.fail()) {
            break;
        }
    }

    plo.close();
    return 0;
}
