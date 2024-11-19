//
// Created by Jonasz Sójka on 15/05/2023.
//

#include "PasswordManagerProgram.h"
#include "UsefulMethods.h"
#include <iostream>

PasswordManagerProgram::PasswordManagerProgram(CommunicationInterface* CI) {
    this->CI=CI;
}


void PasswordManagerProgram::chooseFileEntry() {
    std::string key;
    CI->printCutomMessesage("Podaj klucz do pliku!");
    std::cin >> key;

    CI->printHelloMessesage();

    std::string fileAnswer;
    std::cin >> fileAnswer;

    bool correctAnswer = false;
    while (!correctAnswer) {
        if (fileAnswer == "1") {
            correctAnswer = true;
            std::string path;
            CI->printCutomMessesage("Podaj sciezke: ");
            std::cin >> path;
            bool correctFile = false;
            while (!correctFile) {
                if (!std::filesystem::exists(path) || !FileManager::isFileTxt(path,key)) {
                    CI->printAlert("Podaj poprawna sciezke do pliku!");
                    std::cin >> path;
                } else {
                    PasswordManager passwordManager = PasswordManager(CI, new FileManager(path), key);
                    correctFile = true;
                    passwordManager.getFileManager()->setFilePath(path);
                    this->chooseAvailableTool(passwordManager);
                }
            }
        } else if (fileAnswer == "2") {
            correctAnswer = true;
            CI->printCutomMessesage(
                    "Wybierz plik, ktory bedzie sluzyl do zapisu twoich hasel z posrod wymienioncych: ");
            std::vector<std::filesystem::path> availableFiles{};
            availableFiles = FileManager::getFilesFromDirectory("../cmake-build-debug/", key);
            for (auto &file: availableFiles) {
                CI->printCutomMessesage(file.filename().string());
            }
            std::string chosenfile;
            std::cin >> chosenfile;
            while(!UsefulMethods::containsValue(availableFiles,chosenfile)){
                CI->printCutomMessesage(
                        "Wybierz plik, ktory bedzie sluzyl do zapisu twoich hasel z posrod wymienioncych: ");
                for (auto &file: availableFiles) {
                    CI->printCutomMessesage(file.filename().string());
                }
                CI->printAlert("Wybierz i podaj jeden z wymienionych wyzej plikow!");
                std::cin >> chosenfile;
            }
            PasswordManager passwordManager = PasswordManager(CI, new FileManager(chosenfile), key);
            this->chooseAvailableTool(passwordManager);
        } else {
            CI->printAlert("Wybierz opcje (1/2)!");
            std::cin>>fileAnswer;
        }
    }
}

void PasswordManagerProgram::chooseAvailableTool(PasswordManager& passwordManager) {
    char answerOption;

    bool correctAnswer = false;
    bool powerOff = false;

    while(!powerOff) {
        this->CI->printAvailableTools();
        std::cin >> answerOption;
        correctAnswer=false;
        while (!correctAnswer) {
            switch (answerOption) {
                case 'W':
                case 'w':
                    correctAnswer = true;
                    passwordManager.searchPassword();
                    break;
                case 'S':
                case 's':
                    correctAnswer = true;
                    passwordManager.sortPasswords();
                    break;
                case 'D':
                case 'd':
                    correctAnswer = true;
                    passwordManager.addPassword();
                    break;
                case 'E':
                case 'e':
                    correctAnswer = true;
                    passwordManager.editPassword();
                    break;
                case 'U':
                case 'u':
                    correctAnswer = true;
                    passwordManager.deletePassword();
                    break;
                case 'A':
                case 'a':
                    correctAnswer = true;
                    passwordManager.addCategory();
                    break;
                case 'Q':
                case 'q':
                    correctAnswer=true;
                    powerOff=true;
                    break;
                case 'K':
                case 'k':
                    correctAnswer = true;
                    passwordManager.deleteCategory();
                    break;
                default:
                    this->CI->printAlert("Podaj poprawnie jedna z wymienionych opcji!");
                    this->CI->printAvailableTools();
                    std::cin >> answerOption;
                    break;
            }
        }
    }
}
