//
// Created by Jonasz Sójka on 13/05/2023.
//

#include <iostream>
#include "PasswordManager.h"
#include "CommunicationPanel.h"
#include "CommunicationInterface.h"
#include "FileManager.h"
#include <ctime>
#include "CryptingManager.h"
#include "SafetyChecker.h"
#include <vector>
#include "UsefulMethods.h"
#include "Password.h"
#include <sstream>

PasswordManager::PasswordManager(CommunicationInterface *CI, FileManager *filemanager, std::string key) {
    this->CI = CI;
    this->fileManager = filemanager;
    this->key = key;
    this->categoryList = filemanager->loadCategories(
            "../cmake-build-debug/categories.txt", this->key);
    this->fileManager->setCategoriesFilePath("../cmake-build-debug/categories.txt");
    this->passwordsList = filemanager->loadPasswords(this->fileManager->getFilePath(), this->key);
}

void PasswordManager::addPassword() {
    std::string inputChoice, password;
    bool correctAnswer = false;
    while (!correctAnswer) {
        CI->printCutomMessesage("Czy haslo ma zostac wygenerowane automatycznie? (T/N)");
        std::cin >> inputChoice;
        if (inputChoice == "T" || inputChoice == "t" || inputChoice == "N" || inputChoice == "n") {
            correctAnswer = true;
        } else {
            CI->printAlert("Podaj poprawna odpowiedz: (T/N) albo (t/n)");
        }
    }

    //generowanie automatyczne
    //dlugosc
    int mLength1;
    bool correctAnswer2 = false;
    if (inputChoice == "T" || inputChoice == "t") {
        while (!correctAnswer2) {
            //pobieranie szczegolowych danych dot. automatycznego generowania
            std::string mLength;
            CI->printCutomMessesage("Podaj liczbe znakow, ktora ma zawierac twoje haslo (min. 8)!");
            std::cin >> mLength;

            auto stringToInt = [](const std::string& str) {
                std::istringstream iss(str);
                int number;
                iss >> number;
                return number;
            };

            mLength1=stringToInt(mLength);

            if (!UsefulMethods::isNumber(mLength) || mLength1 <= 7) {
                CI->printAlert("Podaj poprawna odpowiedz: Podaj liczbe naturalna, ktora jest wieksza od 7!");
            }else{
                correctAnswer2= true;
            }
        }

        //duze litery
        bool ifCapitals;
        bool correctAnswer3 = false;
        while (!correctAnswer3) {
            std::string answerCapitals;
            CI->printCutomMessesage("Czy twoje haslo ma zawierac duze litery? (T/N)");
            std::cin >> answerCapitals;
            if (answerCapitals == "T" || answerCapitals == "t") {
                ifCapitals = true;
                correctAnswer3 = true;
            } else if (answerCapitals == "N" || answerCapitals == "n") {
                ifCapitals = false;
                correctAnswer3 = true;
            } else {
                CI->printAlert("Podaj poprawna odpowiedz: (T/N) albo (t/n)");
            }
        }
        //male litery
        bool ifLowerCase;
        bool correctAnswer4 = false;
        while (!correctAnswer4) {
            std::string answerLowerCase;
            CI->printCutomMessesage("Czy twoje haslo ma zawierac male litery? (T/N)");
            std::cin >> answerLowerCase;
            if (answerLowerCase == "T" || answerLowerCase == "t") {
                ifLowerCase = true;
                correctAnswer4 = true;
            } else if (answerLowerCase == "N" || answerLowerCase == "n") {
                ifLowerCase = false;
                correctAnswer4 = true;
            } else {
                CI->printAlert("Podaj poprawna odpowiedz: (T/N) albo (t/n)");
            }
        }

        //znaki specjalne
        bool ifSpecial;
        bool correctAnswer5 = false;
        while (!correctAnswer5) {
            std::string answerSpecial;
            CI->printCutomMessesage("Czy twoje haslo ma zawierac znaki specjalne? (T/N)");
            std::cin >> answerSpecial;
            if (answerSpecial == "T" || answerSpecial == "t") {
                ifSpecial = true;
                correctAnswer5 = true;
            } else if (answerSpecial == "N" || answerSpecial == "n") {
                ifSpecial = false;
                correctAnswer5 = true;
            } else {
                CI->printAlert("Podaj poprawna odpowiedz: (T/N) albo (t/n)");
            }
        }
        password = Password::generatePassword(ifCapitals, ifLowerCase, ifSpecial, mLength1);

        std::string name, category;

        CI->printCutomMessesage("Podaj notke (Nazwa wlasna) dla tego hasla: ");
        std::cin >> name;

        while (UsefulMethods::containsSeparator(FileManager::separator, name)) {
            CI->printAlert(
                    "Podaj notke (Nazwa wlasna) dla tego hasla, nieposiadajace znaku ';'!");
            std::cin >> name;
        }

        bool correctAnswer6 = false;
        while (!correctAnswer6) {
            CI->printCutomMessesage("Lista kategorii do wyboru: ");
            for (const auto &cat: this->categoryList) {
                CI->printCutomMessesage(cat);
            }

            CI->printCutomMessesage("Podaj kategorie hasla: ");
            std::cin >> category;
            //sprawdzenie czy odpowiedz jest poprawna
            if (UsefulMethods::categoryExists(category, this->categoryList)) {
                correctAnswer6 = true;
            } else {
                CI->printAlert("Taka kategoria nie istnieje!");
            }
        }
        std::string www, login, answerLoginWWW;

        bool correctAnswerLogin = false;
        while (!correctAnswerLogin) {
            CI->printCutomMessesage("Czy chcesz dodac strone www i login do swojego hasla? (T/N)");
            std::cin >> answerLoginWWW;
            if (answerLoginWWW == "T" || answerLoginWWW == "t" || answerLoginWWW == "N" || answerLoginWWW == "n") {
                if(answerLoginWWW=="T" || answerLoginWWW=="t"){
                    CI->printCutomMessesage("Podaj strone www dla tego hasla: ");
                    std::cin >> www;

                    while (UsefulMethods::containsSeparator(FileManager::separator, www)) {
                        CI->printAlert(
                                "Podaj strone www dla tego hasla: ");
                        std::cin >> www;
                    }

                    CI->printCutomMessesage("Podaj login dla tego hasla: ");
                    std::cin >> login;

                    while (UsefulMethods::containsSeparator(FileManager::separator, www)) {
                        CI->printAlert(
                                "Podaj login dla tego hasla: ");
                        std::cin >> login;
                    }
                }else{
                    www="";
                    login="";
                }
                correctAnswerLogin = true;
            } else {
                CI->printAlert("Podaj poprawna odpowiedz: (T/N) albo (t/n)");
            }
        }

        passwordsList.push_back(Password(name, password, category,www,login));


    } else if (inputChoice == "N" || inputChoice == "n") {
//pobieranie danych szczegolowych dot. hasla i pobenanie jego samego
        std::string name, category;

        CI->printCutomMessesage("Podaj haslo, ktore chcesz zapisac: ");
        std::cin >> password;

        while (UsefulMethods::containsSeparator(FileManager::separator, password)) {
            CI->printAlert("Podaj haslo, ktore chcesz zapisac nie posiadajace znaku ';'!");
            std::cin >> password;
        }

        CI->printCutomMessesage("Podaj notke (Nazwa wlasna) dla tego hasla: ");
        std::cin >> name;

        while (UsefulMethods::containsSeparator(FileManager::separator, name)) {
            CI->printAlert(
                    "Podaj notke (Nazwa wlasna) dla tego hasla, nieposiadajace znaku ';'!");
            std::cin >> name;
        }

        bool correctAnswer6 = false;
        while (!correctAnswer6) {
            CI->printCutomMessesage("Lista kategorii do wyboru: ");
            for (const auto &cat: this->categoryList) {
                CI->printCutomMessesage(cat);
            }

            CI->printCutomMessesage("Podaj kategorie hasla: ");
            std::cin >> category;
            //sprawdzenie czy podana kategoria istnieje
            if (UsefulMethods::categoryExists(category, this->categoryList)) {
                correctAnswer6 = true;
            } else {
                CI->printAlert("Taka kategoria nie istnieje!");
            }
        }
        //sprawdzenie czy haslo bylo juz uzyte + okreslenie poziomu bezpieczenstwa
        std::vector<std::string> passwordList{};
        for (const auto &passw: passwordsList) {
            passwordList.push_back(passw.getPassw());
        }

        if (SafetyChecker::wasUsedBefore(password, passwordList)) {
            CI->printAlert("Haslo zostalo wczesniej uzyte! Sugorowane dzialanie: edycja hasla na silniejsze!");
        } else {
            CI->printCutomMessesage("Poziom bezpieczenstwa hasla: " + SafetyChecker::howSafeIsPassword(password));
        }
        std::string answerLoginWWW,www,login;
        bool correctAnswerLogin = false;
        while (!correctAnswerLogin) {
            CI->printCutomMessesage("Czy chcesz dodac strone www i login do swojego hasla? (T/N)");
            std::cin >> answerLoginWWW;
            if (answerLoginWWW == "T" || answerLoginWWW == "t" || answerLoginWWW == "N" || answerLoginWWW == "n") {
                if(answerLoginWWW=="T" || answerLoginWWW=="t"){
                    CI->printCutomMessesage("Podaj strone www dla tego hasla: ");
                    std::cin >> www;

                    while (UsefulMethods::containsSeparator(FileManager::separator, www)) {
                        CI->printAlert(
                                "Podaj strone www dla tego hasla: ");
                        std::cin >> www;
                    }

                    CI->printCutomMessesage("Podaj login dla tego hasla: ");
                    std::cin >> login;

                    while (UsefulMethods::containsSeparator(FileManager::separator, www)) {
                        CI->printAlert(
                                "Podaj login dla tego hasla: ");
                        std::cin >> login;
                    }
                }else{
                    www="";
                    login="";
                }
                correctAnswerLogin = true;
            } else {
                CI->printAlert("Podaj poprawna odpowiedz: (T/N) albo (t/n)");
            }
        }

        passwordsList.push_back(Password(name, password, category,www,login));

//        std::cout << "" + name + FileManager::separator + password + FileManager::separator +category << std::endl;
//        std::cout << CryptingManager::encryptData(name + FileManager::separator + password + FileManager::separator +category,3) << std::endl;
//        std::cout << CryptingManager::decryptData(CryptingManager::encryptData(name + FileManager::separator + password + FileManager::separator +category,3),3) << std::endl;
    }
    for(Password p : passwordsList){
        CI->printCutomMessesage(p.toString());
    }
    fileManager->overwriteFileWithPasswords(this->passwordsList,key);
    this->CI->printCorrectResult("Zapisywanie... Gotowe!");
}

void PasswordManager::addCategory() {
    std::string category;

    CI->printCutomMessesage("Podaj nazwe kateogrii, ktora chcesz dodac: ");
    std::cin >> category;

    while (UsefulMethods::containsSeparator(FileManager::separator, category)) {
        CI->printAlert("Podaj nazwe kateogrii, ktora chcesz dodac, ktora nie posiada znaku ';'!");
        std::cin >> category;
    }

    this->categoryList.push_back(category);
    this->fileManager->saveLineToFile(CryptingManager::encryptData(category, this->key), key);
    this->CI->printCorrectResult("Zapisywanie... Gotowe!");
}

void PasswordManager::deleteCategory() {
    std::string category;

    bool correctAnswer = false;
    while (!correctAnswer) {
        CI->printCutomMessesage("Lista kategorii do wyboru: ");
        for (const auto &cat: this->categoryList) {
            CI->printCutomMessesage(cat);
        }

        CI->printCutomMessesage("Wybierz kategorie, ktora chcesz usunac: ");
        std::cin >> category;
        //sprawdzenie czy podana kategoria istnieje
        if (UsefulMethods::categoryExists(category, this->categoryList)) {
            correctAnswer = true;
        } else {
            CI->printAlert("Taka kategoria nie istnieje!");
        }
    }
    auto index = std::find(this->categoryList.begin(), this->categoryList.end(), category);
    this->categoryList.erase(index);
    CI->printCorrectResult("Pomyslnie usunieto kategorie: " + category);

    auto indx = passwordsList.begin();
    while (indx != passwordsList.end()) {
        if (indx->getCat() == category) {
            indx = passwordsList.erase(indx);
        } else {
            ++indx;
        }
    }
    this->fileManager->overwriteFileWithPasswords(this->passwordsList, this->key);
    this->fileManager->overwriteFileWithCategories(this->categoryList, this->key);
    CI -> printCorrectResult("Zmiany zostaly pomyslnie zapisane!");
}

void PasswordManager::searchPassword() {
    std::string category, passw, name, www,login;
    CI->printAlert("W przypadku braku podania parametru, wpisz '-'!");
    CI->printCutomMessesage("Podaj haslo, ktore chcesz wyszukac: ");
    std::cin >> passw;

    while (UsefulMethods::containsSeparator(FileManager::separator, passw)) {
        CI->printAlert("Podaj haslo, ktore chcesz wyszukac nie posiadajace znaku ';'!");
        std::cin >> passw;
    }

    CI->printCutomMessesage("Podaj notke (Nazwa wlasna) wedlug ktorej chcesz wyszukac hasla: ");
    std::cin >> name;

    while (UsefulMethods::containsSeparator(FileManager::separator, name)) {
        CI->printAlert("Podaj notke (Nazwa wlasna) wedlug ktorej chcesz wyszukac hasla, ktora nie posiada znaku ';'!");
        std::cin >> name;
    }

    bool correctAnswer = false;
    while (!correctAnswer) {
        CI->printCutomMessesage("Lista kategorii do wyboru: ");
        for (const auto &cat: this->categoryList) {
            CI->printCutomMessesage(cat);
        }

        CI->printCutomMessesage("Wybierz kategorie hasla wedlug chcesz wyszukac hasla: ");
        std::cin >> category;
        //sprawdzenie czy podana kategoria istnieje
        if (UsefulMethods::categoryExists(category, this->categoryList) || category=="-") {
            correctAnswer = true;
        } else {
            CI->printAlert("Taka kategoria nie istnieje!");
        }
    }

    CI->printCutomMessesage("Podaj strone www, ktora jest przy hasle, ktora chcesz wyszukac: ");
    std::cin >> www;

    while (UsefulMethods::containsSeparator(FileManager::separator, name)) {
        CI->printAlert("Podaj strone www, ktora jest przy hasle, ktora chcesz wyszukac nieposiadajaca znaku ';'!");
        std::cin >> www;
    }

    CI->printCutomMessesage("Podaj login, ktory jest przy hasle, ktory chcesz wyszukac: ");
    std::cin >> login;

    while (UsefulMethods::containsSeparator(FileManager::separator, name)) {
        CI->printAlert("Podaj login, ktory jest przy hasle, ktory chcesz wyszukac nieposiadajacy znaku ';'!");
        std::cin >> login;
    }

    bool searchCategory = true;
    bool searchPassw = true;
    bool searchName = true;
    bool searchWWW = true;
    bool searchLogin = true;

    int countCon = 5;
    if (category == "-") {
        searchCategory = false;
        countCon--;
    }
    if (passw == "-") {
        searchPassw = false;
        countCon--;
    }
    if (name == "-") {
        searchName = false;
        countCon--;
    }
    if (www == "-") {
        searchWWW = false;
        countCon--;
    }
    if (login == "-") {
        searchLogin = false;
        countCon--;
    }

    int countMatching = 0;
    this->CI->printCorrectResult("Pasujace hasla i ich dane: ");
    if (countCon > 0) {
        for (const Password &password: this->passwordsList) {
            int countEq = 0;
            if (searchPassw && password.getPassw() == passw) {
                countEq++;
            }
            if (searchName && password.getName() == name) {
                countEq++;
            }
            if (searchCategory && password.getCat() == category) {
                countEq++;
            }
            if (searchWWW && password.getWww() == www) {
                countEq++;
            }
            if (searchLogin && password.getLogin() == login) {
                countEq++;
            }
            if (countEq == countCon) {
                this->CI->printCutomMessesage(password.toString());
                countMatching++;
            }
        }
        if (countMatching == 0) {
            this->CI->printCorrectResult("Brak pasujacych hasel");
        }
    } else {
        this->CI->printAlert("Brak parametrow!");
    }
}

void PasswordManager::deletePassword() {
    int passNr;
    std::string passNrS;
    std::vector<int> deletePasswordList{};
    int countRound = 0;
    std::string deleteAnswer = "T";
    while (deleteAnswer != "N" && deleteAnswer != "n") {
        if (countRound > 0) {
            bool correctAnswer = false;
            while (!correctAnswer) {
                CI->printCutomMessesage("Czy chcesz usunac jeszcze jakies haslo? (T/N)");
                std::cin >> deleteAnswer;
                if (deleteAnswer == "T" || deleteAnswer == "t" || deleteAnswer == "N" || deleteAnswer == "n") {
                    correctAnswer = true;
                } else {
                    CI->printAlert("Podaj poprawna odpowiedz: (T/N) albo (t/n)");
                }
            }
        }
        if (deleteAnswer == "T" || deleteAnswer == "t") {
            CI->printCutomMessesage("Wszystkie zapisane hasla: ");
            int number = 1;
            for (auto &p: this->passwordsList) {
                CI->printCutomMessesage(std::to_string(number) + ". " + p.toString());
                number++;
            }

            CI->printCutomMessesage("Podaj NUMER hasla z ponizej wymienionych, ktory chcesz usunac (Wprowadz podwojnie): ");
            std::cin >> passNr >> passNrS;

            while (!UsefulMethods::isNumber(passNrS) && passNr > 0 && passNr <= this->passwordsList.size()) {
                CI->printCutomMessesage("Wszystkie zapisane hasla: ");
                for (auto &p: this->passwordsList) {
                    CI->printCutomMessesage(p.toString());
                }
                CI->printAlert("Podaj NUMER hasla z ponizej wymienionych, ktory chcesz usunac (Wprowadz podwojnie): ");
                std::cin >> passNr;
            }
            deletePasswordList.push_back(passNr);
            countRound++;
        }
    }

    if (deletePasswordList.size() > 1) {
        std::string confirmAnswer;
        bool correctAnswer = false;
        while (!correctAnswer) {
            CI->printCutomMessesage("Czy napewno chcesz usunac wiecej niz 1 haslo? (T/N)");
            std::cin >> confirmAnswer;
            if (confirmAnswer == "T" || confirmAnswer == "t" || confirmAnswer == "N" || confirmAnswer == "n") {
                correctAnswer = true;
            } else {
                CI->printAlert("Podaj poprawna odpowiedz: (T/N) albo (t/n)");
            }
        }
        if (confirmAnswer == "T" || confirmAnswer == "t") {
            int number = 1;
            for (auto round = this->passwordsList.begin(); round != this->passwordsList.end();) {
                if (std::find(deletePasswordList.begin(), deletePasswordList.end(), number) !=
                    deletePasswordList.end()) {
                    round = this->passwordsList.erase(round);
                } else {
                    ++round;
                }
                number++;
            }

            for (auto &p: passwordsList) {
                CI->printCutomMessesage(p.toString());
            }
            this->fileManager->overwriteFileWithPasswords(this->passwordsList, this->key);
            CI->printCorrectResult("Usuwanie... Hasla zostaly pomyslnie usuniete");
        } else {
            CI->printCorrectResult("Zadne haslo nie zostalo usuniete!");
        }
    } else if (deletePasswordList.size() == 1) {
        std::string confirmAnswer;
        bool correctAnswer = false;
        while (!correctAnswer) {
            CI->printCutomMessesage("Czy napewno chcesz usunac te haslo? (T/N)");
            std::cin >> confirmAnswer;
            if (confirmAnswer == "T" || confirmAnswer == "t" || confirmAnswer == "N" || confirmAnswer == "n") {
                correctAnswer = true;
            } else {
                CI->printAlert("Podaj poprawna odpowiedz: (T/N) albo (t/n)");
            }
        }
        if (confirmAnswer == "T" || confirmAnswer == "t") {
            int number = 1;
            for (auto round = this->passwordsList.begin(); round != passwordsList.end(); round++) {
                if (std::find(deletePasswordList.begin(), deletePasswordList.end(), number) !=
                    deletePasswordList.end()) {
                    this->passwordsList.erase(round);
                    break;
                }
                number++;
            }
            this->fileManager->overwriteFileWithPasswords(this->passwordsList, this->key);
            CI->printCorrectResult("Usuwanie... Haslo zostalo pomyslnie usuniete!");
        } else {
            CI->printCorrectResult("Zadne haslo nie zostalo usuniete");
        }
    } else {
        CI->printAlert("Nie podano elementow do usuniecia");
    }
}

void PasswordManager::sortPasswords() {
    std::vector<Password> sortedPasswords = this->passwordsList;

    std::sort(sortedPasswords.begin(), sortedPasswords.end(), Password::comparePasswords);

    CI->printCorrectResult("Posortowana lista twoich hasel: ");
    for (const auto& password : sortedPasswords) {
        CI->printCutomMessesage(password.toString());
    }
}

FileManager *PasswordManager::getFileManager() const {
    return fileManager;
}

void PasswordManager::editPassword() {
    std::string category, passw, name,categorye, passwe, namee,www,wwwe,login,logine;
    CI->printCutomMessesage("Twoje hasla: ");
    for(auto p : this->passwordsList){
        CI->printCutomMessesage(p.toString());
    }
    //pobranie danych o hasle
    CI->printCutomMessesage("Podaj haslo, ktore chcesz edytowac: ");
    std::cin >> passw;

    while (UsefulMethods::containsSeparator(FileManager::separator, passw)) {
        CI->printAlert("Podaj haslo, ktore chcesz wyszukac nie posiadajace znaku ';'!");
        std::cin >> passw;
    }

    CI->printCutomMessesage("Podaj notke (Nazwa wlasna) ktora jest przy hasle, ktore chcesz edytowac: ");
    std::cin >> name;

    while (UsefulMethods::containsSeparator(FileManager::separator, name)) {
        CI->printAlert("Podaj notke (Nazwa wlasna) ktora jest przy hasle, ktore chcesz edytowac nieposiadajace znaku ';'!");
        std::cin >> name;
    }

    bool correctAnswer = false;
    while (!correctAnswer) {
        CI->printCutomMessesage("Wybierz kategorie hasla, ktore chcesz edytowac: ");
        std::cin >> category;
        //sprawdzenie czy podana kategoria istnieje
        if (UsefulMethods::categoryExists(category, this->categoryList)) {
            correctAnswer = true;
        } else {
            CI->printAlert("Taka kategoria nie istnieje!");
        }
    }

    CI->printCutomMessesage("Podaj strone www, ktora jest przy hasle, ktora chcesz edytowac: ");
    std::cin >> www;

    while (UsefulMethods::containsSeparator(FileManager::separator, name)) {
        CI->printAlert("Podaj strone www, ktora jest przy hasle, ktora chcesz edytowac nieposiadajaca znaku ';'!");
        std::cin >> www;
    }
    if(www=="-"){
        www="";
    }

    CI->printCutomMessesage("Podaj login, ktory jest przy hasle, ktory chcesz edytowac: ");
    std::cin >> login;

    while (UsefulMethods::containsSeparator(FileManager::separator, name)) {
        CI->printAlert("Podaj login, ktory jest przy hasle, ktory chcesz edytowa nieposiadajacy znaku ';'!");
        std::cin >> login;
    }
    if(login=="-"){
        login="";
    }

    //na co chcemy edytowac
    CI->printCutomMessesage("Podaj haslo, na ktore ma byc zmienione: ");
    std::cin >> passwe;

    while (UsefulMethods::containsSeparator(FileManager::separator, passwe)) {
        CI->printAlert("Podaj haslo, na ktore ma byc zmienione nie posiadajace znaku ';'!");
        std::cin >> passwe;
    }

    CI->printCutomMessesage("Podaj notke (Nazwa wlasna) edytowana: ");
    std::cin >> namee;

    while (UsefulMethods::containsSeparator(FileManager::separator, namee)) {
        CI->printAlert("Podaj notke (Nazwa wlasna) edytowana, nie posiadajaca znaku ';'!");
        std::cin >> namee;
    }

    bool correctAnswer2 = false;
    while (!correctAnswer2) {
        CI->printCutomMessesage("Lista kategorii do wyboru: ");
        for (const auto &cat: this->categoryList) {
            CI->printCutomMessesage(cat);
        }
        CI->printCutomMessesage("Wybierz kategorie hasla, ktore chcesz edytowac: ");
        std::cin >> categorye;
        //sprawdzenie czy podana kategoria istnieje
        if (UsefulMethods::categoryExists(categorye, this->categoryList)) {
            correctAnswer2 = true;
        } else {
            CI->printAlert("Taka kategoria nie istnieje!");
        }
    }
    CI->printCutomMessesage("Podaj strone www, ktora jest przy hasle, ktora chcesz edytowac: ");
    std::cin >> wwwe;

    while (UsefulMethods::containsSeparator(FileManager::separator, name)) {
        CI->printAlert("Podaj strone www, ktora jest przy hasle, ktora chcesz edytowac nieposiadajaca znaku ';'!");
        std::cin >> wwwe;
    }
    if(wwwe=="-"){
        wwwe="";
    }

    CI->printCutomMessesage("Podaj login, ktory jest przy hasle, ktory chcesz edytowac: ");
    std::cin >> logine;

    while (UsefulMethods::containsSeparator(FileManager::separator, name)) {
        CI->printAlert("Podaj login, ktory jest przy hasle, ktory chcesz edytowa nieposiadajacy znaku ';'!");
        std::cin >> logine;
    }
    if(logine=="-"){
        logine="";
    }
    int count=0;
    for(auto &p : this->passwordsList){
        if(p.getCat()==category && p.getPassw()==passw && p.getName()==name && p.getWww()==www && p.getLogin()==login){
            p.setCat(categorye);
            p.setPassw(passwe);
            p.setName(namee);
            p.setWww(wwwe);
            p.setLogin(logine);
            count++;
            break;
        }
    }
    count==0?CI->printAlert("Nie znaleziono takiego hasla"):CI->printCorrectResult("Haslo zostalo pomyslnie zmienione");
    fileManager->overwriteFileWithPasswords(this->passwordsList,this->key);
}
