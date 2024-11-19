//
// Created by krzys on 16.05.2023.
//

#include "Utilities.h"

bool isNumber(const std::string &str) {
    if (str.empty())
        return false;
    for (char c: str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool doesStringContainWhitespace(const std::string &str) {
    for (auto ch: str)
        if (std::isspace(ch))
            return true;

    return false;
}

int countCharAppInString(const std::string &text, char character) {
    int licznik = 0;
    for (char c: text) {
        if (c == character) {
            licznik++;
        }
    }
    return licznik;
}

std::string generatePassword(int size, bool upperLowerCase, bool specialCharacters) {
    std::string pass;

    std::string lowercase = "abcdefghijklmnopqrstuvwxyz";

    std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    std::string special = "!\"#$%&'()*+,-./:<=>?@[\\]^_`{|}~";

    int specialCharAmount = 0;
    if (specialCharacters)
        specialCharAmount = (std::rand() % (size / 2)) + 1;

    int uppercaseAmount = 0;
    if (upperLowerCase)
        uppercaseAmount = (std::rand() % (size / 2)) + 1;

    for (int i = 0; i < size; i++) {
        if (i < specialCharAmount)
            pass += special[std::rand() % special.size()];
        else if (i < uppercaseAmount + specialCharAmount)
            pass += uppercase[std::rand() % uppercase.size()];
        else
            pass += lowercase[std::rand() % lowercase.size()];
    }

    for (int i = 0; i < size; i++) {
        int i1 = std::rand() % size;
        int i2;
        do {
            i2 = std::rand() % size;
        } while (i1 == i2);
        char tmp = pass[i1];
        pass[i1] = pass[i2];
        pass[i2] = tmp;
    }

    return pass;
}

bool isNumber(const char &ch) {
    return ch >= '0' && ch <= '9';
}

std::vector<std::string> toLowercase(std::vector<std::string> &vec) {
    for (auto &str: vec)
        std::transform(str.begin(), str.end(), str.begin(),
                       [](char ch) {
                           return std::tolower(ch);
                       }
        );

    return vec;
}
