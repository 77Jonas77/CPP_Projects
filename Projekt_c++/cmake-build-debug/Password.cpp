//
// Created by Jonasz Sójka on 15/05/2023.
//

#include "Password.h"

Password::Password(std::string name, std::string passw, std::string cat, std::string www, std::string login) {
    this->name = name;
    this->passw = passw;
    this->cat = cat;
    this->www = www;
    this->login = login;
}

std::string Password::generatePassword(bool ifC, bool ifL, bool ifS, int length) {
    std::string password;
    std::string uppercaseLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string lowercaseLetters = "abcdefghijklmnopqrstuvwxyz";
    std::string specialCharacters = "!@#$%^&*()";
    std::string numbers = "0123456789";

    //okreslenie z jakich znakow ma sie skladac haslo
    std::string characters;
    characters += numbers;
    if (ifC) {
        characters += uppercaseLetters;
    }
    if (ifL) {
        characters += lowercaseLetters;
    }
    if (ifS) {
        characters += specialCharacters;
    }

    std::srand(std::time(NULL));

    // Wygeneruj losowe hasło o podanej długości
    for (int i = 0; i < length; i++) {
        int randomIndex = std::rand() % characters.length();
        password += characters[randomIndex];
    }
    return password;
}

const std::string &Password::getName() const {
    return name;
}

void Password::setName(const std::string &nam) {
    Password::name = nam;
}

const std::string &Password::getPassw() const {
    return passw;
}

void Password::setPassw(const std::string &pass) {
    Password::passw = pass;
}

const std::string &Password::getCat() const {
    return cat;
}

void Password::setCat(const std::string &cate) {
    Password::cat = cate;
}

std::string Password::toString() const {
    return "Nazwa wlasna: " + this->getName() + " Haslo: " + this->getPassw() + " Kategoria: " + this->getCat() + " Strona WWW: " + this->getWww() + " Login: " + this->getLogin();
}

bool Password::comparePasswords(const Password & p1, const Password & p2) {
    if (p1.getName() != p2.getName()) {
        return p1.getName() < p2.getName();
    } else if (p1.getPassw() != p2.getPassw()) {
        return p1.getPassw() < p2.getPassw();
    } else {
        return p1.getCat() < p2.getCat();
    }
}

const std::string &Password::getWww() const {
    return www;
}

void Password::setWww(const std::string &www) {
    Password::www = www;
}

const std::string &Password::getLogin() const {
    return login;
}

void Password::setLogin(const std::string &login) {
    Password::login = login;
}
