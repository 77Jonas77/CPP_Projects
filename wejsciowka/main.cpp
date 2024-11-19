#include <iostream>
#include <fstream>
#include <map>

int main() {
    std::string dirname;
    std::cin >> dirname;
    std::fstream fileIn;
    std::map<std::string, int> count_numbers;
    auto dirPathRec = std::filesystem::recursive_directory_iterator(dirname);

    for (const auto &dir: dirPathRec) {
        if (dir.is_directory()) {
            auto dirPathRec2 = std::filesystem::recursive_directory_iterator(dir);
            for (const auto &dir2: dirPathRec2) {
                std::fstream fileIn;
                fileIn.open(dir2.path(), std::ios::in);
                std::string number;
                if (fileIn.is_open()) {
                    while (fileIn >> number) {
                        count_numbers[number]++;
                    }
                }
            }
        } else {
            std::fstream fileIn;
            fileIn.open(dir.path(), std::ios::in);
            std::string number;
            if (fileIn.is_open()) {
                while (fileIn >> number) {
                    count_numbers[number]++;
                }
            }
        }
    }
    for (const auto &pair: count_numbers) {
        std::cout << pair.first << " " << pair.second << std::endl;
    }
    return 0;
}