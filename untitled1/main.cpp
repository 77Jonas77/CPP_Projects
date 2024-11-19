#include <iostream>
#include <cmath>
//using namespace std;
using std::cout;
using std::endl;
//void fun();
//void fun1();
void fun1();
void fun();

double BMI(double wzrost, double waga) {
    return waga / pow(wzrost, 2);
}

void show(int max, int l1, int l2, int l3) {
    for (int i = max; i > 0; i--) {
        cout << (l1 >= i ? "*" : " ");
        cout << (l2 >= i ? "*" : " ");
        cout << (l3 >= i ? "*" : " ");
        cout << endl;
    }
}

int main() {
    bool b1 = 0; //wszystko poza zerem jest prawda
    bool b2 = 5;
    cout << b1 << endl; //0
    cout << (b1 == false) << endl; //1
    cout << (b2 == 5) << endl; //0
    double d1, d2;
    std::cin >> d1 >> d2;
//zadanie1

    double wzrost, waga;
    cout << "Podaj wzrost: ";
    std::cin >> wzrost;
    cout << "Podaj wage: ";
    std::cin >> waga;
    cout << BMI(wzrost, waga) << endl;

//zadanie 2
    cout << "Podaj trzy nieujemne liczby calkowite" << endl;
    int l1, l2, l3;
    std::cin >> l1;
    std::cin >> l2;
    std::cin >> l3;
    show(8, l1, l2, l3);
    //zadanie 3
    int l = 1, max = 0;
    do {
        int suma = 0;
        std::cin >> l;
        while (l > 0) {
            suma += l % 10;
            l /= 10;
        }
        if (suma > max) {
            max = suma;
        }
    } while (l != 0);
    cout << max << endl;
}
    void fun() {
        fun1();
    }
    void fun1() {
        fun();
    }