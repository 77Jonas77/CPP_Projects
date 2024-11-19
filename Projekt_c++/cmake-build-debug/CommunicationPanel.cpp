//
// Created by Jonasz Sójka on 14/05/2023.
//

#include "CommunicationPanel.h"
#include <string>
#include <iostream>

void CommunicationPanel::printCutomMessesage(std::string msg) const{
    std::cout << msg << std::endl;
}

void CommunicationPanel::printHelloMessesage() const {
    std::cout << "\033[31mM\033[33me\033[32mn\033[36ma\033[34md\033[35mz\033[31me\033[33mr \033[32mH\033[36ma\033[34ms\033[35me\033[31ml\033[33m\033[0m" << std::endl;
    std::cout << "Czesc! Wybierz jedna z dostepnych opcji: " << std::endl << "1. Podaj bezposrednia sciezke (1)" << std::endl << "2. Wybierz jedna z dostepnych sciezek (2)" << std::endl;
}

void CommunicationPanel::printAvailableTools() const {
    std::cout << std::endl;
    std::cout << "\033[31mM\033[33me\033[32mn\033[36ma\033[34md\033[35mz\033[31me\033[33mr \033[32mH\033[36ma\033[34ms\033[35me\033[31ml\033[33m \033[32m-\033[36m \033[34mN\033[35ma\033[31mr\033[33mz\033[32me\033[36md\033[33mz\033[32mi\033[36ma\033[34m\033[0m" << std::endl;
    std::cout << "Tutaj znajduja sie dostepne narzedzia, ktore pomoga ci w zarzadzaniu twoimi haslami! Wybieranie odbywa sie za pomoca wpisania litery reprezentujaca dana opcje (Po lewej stronie)" << std::endl;
    std::cout << "(W/w) - Wyszukaj hasla" << std::endl;
    std::cout << "(S/s) - Posortuj hasla" << std::endl;
    std::cout << "(D/d) - Dodaj haslo" << std::endl;
    std::cout << "(E/e) - Edytuj haslo"<< std::endl;
    std::cout << "(U/u) - Usun haslo"<< std::endl;
    std::cout << "(A/a) - Dodaj kategorie"<< std::endl;
    std::cout << "(K/k) - Usun kategorie"<< std::endl;
    std::cout << "(Q/q) - Zamknij aplikacje (powerOff)"<< std::endl;
    std::cout << "\033[31mPAMIETAJ! ZNAK '-' jest zarezerwowany dla okreslenia braku parametru, ';' jest zarezerwowany jako separator w pliku. Uzywaj tych znakow wedle tej instrukcji!\033[0m" << std::endl;
}

void CommunicationPanel::printAlert(std::string msg) const {
    std::cout << "\033[31m" << msg << "\033[0m" << std::endl;
}

void CommunicationPanel::printCorrectResult(std::string msg) const {
    std::cout << "\033[32m" << msg << "\033[0m" << std::endl;
}


