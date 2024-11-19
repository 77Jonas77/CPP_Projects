//
// Created by krzys on 14.05.2023.
//

#include "Password.h"

Password::Password(const std::string &name, const std::string &password, const std::string &category,
                   const std::string &webpage, const std::string &login) {
    Password::name = name;
    Password::password = password;
    Password::category = category;
    Password::webpage = webpage;
    Password::login = login;
}

const std::string &Password::getName() const {
    return name;
}

void Password::setName(const std::string &name) {
    Password::name = name;
}

const std::string &Password::getPassword() const {
    return password;
}

void Password::setPassword(const std::string &password) {
    Password::password = password;
}

const std::string &Password::getCategory() const {
    return category;
}

void Password::setCategory(const std::string &category) {
    Password::category = category;
}

const std::string &Password::getWebpage() const {
    return webpage;
}

void Password::setWebpage(const std::string &webpage) {
    Password::webpage = webpage;
}

const std::string &Password::getLogin() const {
    return login;
}

void Password::setLogin(const std::string &login) {
    Password::login = login;
}

std::vector<std::string> Password::toVector() const {
    std::vector<std::string> passAsVector;
    passAsVector.push_back(name);
    passAsVector.push_back(password);
    passAsVector.push_back(category);
    passAsVector.push_back(webpage);
    passAsVector.push_back(login);
    return passAsVector;
}

std::ostream &operator<<(std::ostream &ostream, const Password &password) {
    std::string passToStr = password.name + " \033[1;97m|\033[0m " +
                            password.password + " \033[1;97m|\033[0m " +
                            password.category + " \033[1;97m|\033[0m " +
                            (password.webpage.empty() ? "-" : password.webpage) + " \033[1;97m|\033[0m " +
                            (password.login.empty() ? "-" : password.login);
    return ostream << passToStr;
}

std::string Password::toFileLine(char separator) const {
    std::string line;
    line =  name + separator +
            password + separator +
            category + separator +
            webpage + separator +
            login;
    return line;
}
