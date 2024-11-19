//
// Created by krzys on 14.05.2023.
//

#include "Encryptor.h"

Encryptor::Encryptor() = default;

Encryptor::Encryptor(const std::string &key) {
    Encryptor::key = key;
    sumOfKey = 0;
    for (auto ch: key)
        sumOfKey += ch;
    sumOfKey %= 4;
    sumOfKey+=2;
}

std::string Encryptor::encryptString(const std::string &text) const {
    std::string encrypted;
    for (int i = 0; i < text.size(); i++)
        encrypted += char(~((33 + text.at(i) + key.at(i % key.size())) ^ key.at(i % key.size())));

    for (int i = 0; i < encrypted.size(); i++) {
        if (i % sumOfKey == 0)
            encrypted.insert(i + 1, 1, char(33 + (std::rand() % (126 - 33 + 1))));
    }
    return encrypted;
}

std::string Encryptor::decipherString(const std::string &text) const {
    std::string encrypted;

    bool skipNextSign = false;
    for (int i = 0; i < text.size(); i++) {
        if (skipNextSign) {
            skipNextSign = false;
            continue;
        }
        if (i % sumOfKey == 0)
            skipNextSign = true;
        encrypted += text[i];
    }

    std::string deciphered;
    for (int i = 0; i < encrypted.size(); i++) {
        deciphered += char((~encrypted.at(i) ^ key.at(i % key.size())) - key.at(i % key.size()) - 33);
    }
    return deciphered;
}
