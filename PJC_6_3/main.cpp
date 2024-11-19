#include <iostream>
#include <fstream>
#include <string>

int getLinesCount(std::string filePath);

int sumInFile(std::string filePath);

int main() {
    std::fstream file;
    file.open("plik.txt", std::ios::in);
    if (file.is_open()) {
        file << 22 << '\n';
        file << 26 << '\n';
    }

    std::cout << getLinesCount("plik.txt") << std::endl;
    std::cout << sumInFile("plik.txt") << std::endl;

    file.close();
    return 0;
}

int getLinesCount(std::string filePath) {
    std::fstream filex;
    filex.open(filePath, std::ios::in);
    int count = 0;
    if (filex.is_open()) {
        std::string line;
        while (std::getline(filex, line))
            count++;
    }
    filex.close();
    return count;
}

int sumInFile(std::string filePath) {
    std::fstream filex;
    filex.open(filePath, std::ios::in);
    int sum = 0;
    if (filex.is_open()) {
        int l;
        while (filex >> l) {
            sum += l;
        }
    }
    filex.close();
    return sum;
}
