//
// Created by krzys on 14.05.2023.
//

#include "UserInterface.h"

using std::cout;
using std::cin;
using std::endl;

void displayWelcome() {
    cout << "\033[1;3;93mWelcome in Password Manager!\033[0m" << endl;
}

void displayFileMenu() {
    displayRequest("Where is the file with passwords located?");
    cout << "\033[1;3;34m1\033[0m - in current directory" << endl;
    cout << "\033[1;3;34m2\033[0m - in custom path (enter the path from keyboard)" << endl;
}

std::string getStringDataFromUser() {
    std::string line;
    do {
        if (line.find(FileManager::SEPARATOR) != std::string::npos)
            displayError("Data cannot contain ';'");
        std::getline(std::cin, line);
    } while (line.find(FileManager::SEPARATOR) != std::string::npos);
    return line;
}

void displayPasswords(const std::vector<Password> &passwords) {
    displayDefaultMessage("  (Name \033[1;97m|\033[0m Password \033[1;97m|\033[0m Category \033[1;97m|\033[0m Website \033[1;97m|\033[0m Login)");
    int i = 1;
    for (const auto &p: passwords)
        cout << "\033[1;3;35m" << i++ << ")\033[0m " << p << endl;
}

void displayPasswordsWithEnter(const std::vector<Password> &passwords) {
    displayPasswords(passwords);
    cout << "Press \033[1mENTER\033[0m to go back to main menu" << endl;
    std::string s;
    std::getline(cin, s);
}

void displayError(const std::string &message) {
    cout << "\033[1;31m" << message << "\033[0m" << endl;
}

void displayIncorrectInput() {
    displayError("Entered an incorrect value");
}

void displayGivenFiles(const std::vector<std::filesystem::path> &files) {
    displayRequest("Which file do you want to choose?");
    for (int i = 0; i < files.size(); i++) {
        std::cout << "\033[1;3;34m" << i + 1 << "\033[0m - " << files.at(i).filename() << std::endl;
    }
}

void displayDefaultMessage(const std::string &message) {
    cout << message << endl;
}

void displayRequest(const std::string &request) {
    cout << "\033[1;97m" << request << "\033[0m" << endl;
}

void displaySuccess(const std::string &message) {
    cout << "\033[1;3;32m" << message << "\033[0m" << endl;
}

void displayMainMenu() {
    displayRequest("What do you want to do?");
    cout << "\033[1;3;34m1\033[0m - display all passwords" << endl;
    cout << "\033[1;3;34m2\033[0m - look up passwords by parameters" << endl;
    cout << "\033[1;3;34m3\033[0m - sort passwords by parameters" << endl;
    cout << "\033[1;3;34m4\033[0m - add new password" << endl;
    cout << "\033[1;3;34m5\033[0m - edit already existing password" << endl;
    cout << "\033[1;3;34m6\033[0m - delete password" << endl;
    cout << "\033[1;3;34m7\033[0m - add new category" << endl;
    cout << "\033[1;3;34m8\033[0m - delete category and all it's passwords" << endl;
    cout << "\033[1;3;34m0\033[0m - exit" << endl;
}

void displayCategoriesToChoose(const std::vector<std::string> &categories) {
    for (int i = 0; i < categories.size(); i++) {
        cout << "\033[1;3m" << i + 1 << "\033[0m - " << categories.at(i) << endl;
    }
}

void displaySortParameters() {
    cout << "\033[1;3;34m1\033[0m - name" << endl;
    cout << "\033[1;3;34m2\033[0m - password" << endl;
    cout << "\033[1;3;34m3\033[0m - category" << endl;
    cout << "\033[1;3;34m4\033[0m - website" << endl;
    cout << "\033[1;3;34m5\033[0m - login" << endl;
}
