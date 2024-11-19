//
// Created by Jonasz Sójka on 13/05/2023.
//

#ifndef PROJEKT_C___PASSWORDMANAGER_H
#define PROJEKT_C___PASSWORDMANAGER_H

#include <string>
#include <array>
#include "CommunicationPanel.h"
#include "FileManager.h"
#include "CryptingManager.h"
#include <vector>
#include "Password.h"
#include <filesystem>

/**
 * @class PasswordManager Klasa odpowiadająca za zarządzanie hasłami i kategoriami.
 */
class PasswordManager {
    std::vector<std::string> categoryList;
    CommunicationInterface* CI;
    FileManager* fileManager;
    std::vector<Password> passwordsList;
    std::string key;
public:

    PasswordManager(CommunicationInterface*, FileManager*, std::string);
/**
 * Metoda pobierajaca od uzytkownika informajce i wyswietlajaca hasla/rekordy informacji, ktore pasuja do okreslonych parametrow
 */
    void searchPassword(); //szuka po parametrach i uzytkownik bedzie wybieral kategoria
/**
 * Metoda wyswietlajaca posortowane rekordy
 */
    void sortPasswords();
/**
 * Metoda pobierajaca informacje od uzytkownika i odraz dodajaca haslo okreslone wedlug parametrow uzytkownika do pliku.
 */
    void addPassword(); //haslo + kategoria + nazwa
/**
 * Metoda, ktora pozwala na edycje konkretnego hasla (opisanego wedlug wprowadzonych parametrow) na inne, ktore zostanie wygenerowane na podstawie wprowadzonych przez uzytykownika parametrow
 */
    void editPassword();
/**
 * Metoda, sluzaca do usuwania jednego lub wiecej haslel wedlug wprowadzonych przez uzytkownika parametrow
 */
    void deletePassword(); //czy ma byc po nazwie wlasnej
/**
 * Metoda, ktora umozliwia wprowadzanie nowej kategorii
 */
    void addCategory();
/**
 * Metoda, ktora usuwa konkretna kategorie (ktora uzytkownik wybiera)
 */
    void deleteCategory();

    FileManager *getFileManager() const;

    ~PasswordManager() {
        delete fileManager;
    }

};

#endif //PROJEKT_C___PASSWORDMANAGER_H
