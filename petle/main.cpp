#include <iostream>

int main() {

    int liczba;
    std::cin >> liczba;

    int suma = 0, iloczyn = 1;

    while (liczba > 0) { //681
        suma = suma + liczba % 10; // suma+=liczba%10
        iloczyn = liczba % 10 * iloczyn;
        liczba = liczba / 10; // liczba/=10;
    }

    return 0;
}
