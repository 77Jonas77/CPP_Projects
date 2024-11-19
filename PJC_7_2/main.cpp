#include <iostream>
#include <string>
#include <fstream>
#include <map>

int main() {
    auto dirPath = std::string("/Users/jonaszsojka/CLionProjects/PJC_7_2/cmake-build-debug/heh");
    auto dirPathRec = std::filesystem::recursive_directory_iterator(dirPath);
    std::map < std::string, int> count_words;

    int max = 0;
    std::string maxWord;

    for(const auto& dir : dirPathRec){
        if(dir.is_directory())
            continue;
        std::fstream fileIn;
        fileIn.open(dir.path(),std::ios::in);
        std::string word;
        if(fileIn.is_open()){
            while(fileIn>>word){
                count_words[word]++;
            }
        }
        for(const auto& pair: count_words){
            if(pair.second>max){
                max=pair.second;
                maxWord=pair.first;
            }
        }
    }
    std::cout << maxWord << std::endl;
    return 0;
}
