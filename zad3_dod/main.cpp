#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <string>

//Znajdywanie najliczniejszych grup anagramów - nie bylo na lekcji i nie ma rozwiazania

std::vector<std::vector<std::string>> largestAnagramGroupsFrom(const std::string &text) {
    std::vector<std::vector<std::string>> result;
    std::map<std::string, std::vector<std::string>> countWords;
    std::map<std::string, bool> bannedWords;
    std::string word;

    for (auto letter = text.begin(); letter != text.end(); ++letter) {
        if (std::isalpha(*letter)) {
            word += std::tolower(*letter);
        } else if (!word.empty()) {
            if(!bannedWords[word]) {
                bannedWords[word] = true;
                std::string tmpWord=word;
                std::sort(word.begin(), word.end());
                countWords[word].push_back(tmpWord);
                word.clear();
            }
        }
    }

    if (!word.empty()) {
        std::sort(word.begin(), word.end());
        countWords[word].push_back(word);
    }

    size_t maxGroupSize = 0;
    for (auto &[key, group]: countWords) {
        if (group.size() > maxGroupSize) {
            maxGroupSize = group.size();
        }
    }

    for (auto &[key, group]: countWords) {
        if (group.size() == maxGroupSize) {
            result.push_back(group);
        }
    }

    return result;
}


int main() {
    std::vector<std::vector<std::string>> v = largestAnagramGroupsFrom("abab baba bbaa, aabb, asd, dsa, asd, addad, ddaa, aadd, adad, dada");
    for(auto group : v ){
        for(auto word : group ){
            std::cout << word << ' ';
        }
        std::cout<<std::endl;
    }
    return 0;
}
