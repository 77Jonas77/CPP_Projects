#include <iostream>
#include <set>

//FILTROWANIE SLOW - BRAK ROZWIAZANIA + NIE BYLO NA LEKCJI

std::vector<std::string> filtered(const std::vector<std::string>& words, const std::set<std::string>& bannedWords) {
    std::vector<std::string> result;
    for (const auto& word : words) {
        if (bannedWords.count(word) == 0) {
            result.push_back(word);
        }
    }
    return result;
}

auto main() -> int {
    std::vector<std::string> words{"Essa", "kowalski", "adam", "mama", "kiwi", "dzien"};
    std::set<std::string> bannedWords{"Essa", "adam", "dzien"};

    auto filteredWords = filtered(words, bannedWords);

    for (const auto& word : filteredWords) {
        std::cout << word << std::endl;
    }
    return 0;
}
