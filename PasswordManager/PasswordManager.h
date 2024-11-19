//
// Created by krzys on 14.05.2023.
//

#ifndef PASSWORDMANAGER_PASSWORDMANAGER_H
#define PASSWORDMANAGER_PASSWORDMANAGER_H

#include <filesystem>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include "Password.h"
#include "Encryptor.h"
#include "FileManager.h"
#include "Utilities.h"
#include "UserInterface.h"

class PasswordManager {
    std::vector<Password> passwords;
    std::vector<std::string> categories;
    Encryptor encryptor;

public:
    /**
     * @brief Domyślny konstruktor, nie inicjujący żadnych pól obiektowych
     */
    PasswordManager();

    /**
     * @brief Konstruktor tworzący nowy obiekt klasy PasswordManager
     *
     * Tworzy nowy obiekt klasy PasswordManager i inicjuje jego pola obiektowe.
     * Tworzy obiekt klasy Encryptor, który będzie 'maszyną szyfrującą', dla obecnego działania programu.
     * Odczytuje wszystkie kategorie z pliku z kategoriami i wpisuje je w vector.
     * Odczytuje wszystkie hasła z pliku z hasłami, tworzy z nich obiekty klasy Password i wpisuje je do vector'a.
     * Jeśli w pliku z hasłami po odszyfrowaniu, znajdują się kategorie, które jeszcze nie istnieją, pyta się użytkownika,
     * czy chce on je również dodać do pliku z kategoriami.
     *
     * @param passwords - vector z wszystkimi liniami z odczytanego pliku
     * @param key - klucz, który będzie służył do odszyfrowania linii z pliku
     */
    PasswordManager(const std::vector<std::string> &passwords, const std::string &key);

    /**
     * @return Zwraca referencję do obiektu klasy Encryptor, będącego 'maszyną szyfrującą' podczas obecnego działania programu
     */
    [[nodiscard]] const Encryptor &getEncryptor() const;

    /**
     * @return Zwraca referencję do vector'a haseł, które zostały odczytane z pliku
     */
    [[nodiscard]] const std::vector<Password> &getPasswords() const;

    /**
     * @return Zwraca referencję do vector'a kategorii odczytanych z pliku
     */
    [[nodiscard]] const std::vector<std::string> &getCategories() const;

    /**
     * @brief Metoda odpowiadająca za mechanizm wyszukiwania haseł
     *
     * Metoda wybiera te hasła z vector'a z hasłami, które spełniają wszystkie z podanych warunków,
     * a następnie dodaje je do vector'a zwracanego
     *
     * @param parameters - vector parametrów, które mają zostać spełnione, aby hasło zostało uznane za to szukane
     * @return Zwraca vector haseł, które spełniają podane założenia
     */
    [[nodiscard]] std::vector<Password> searchPassword(std::vector<std::string> parameters) const;

    void addPassword(const std::vector<std::string> &passData, FileManager &fileManager);

    void modifyPassword(int passwordIndex, int parameterIdentifier, const std::string &newValue);

    void removePassword(int index);

    void addCategory(const std::string &catName);

    [[nodiscard]] bool doesCategoryAlreadyExist(const std::string &catName) const;

    [[nodiscard]] std::string getNewestCategory() const;

    [[nodiscard]] std::vector<std::string> getPasswordVectorToFile() const;

    void removeCategory(int index);

    [[nodiscard]] std::string getPasswordAtAsString(int index) const;

    [[nodiscard]] std::set<int> getPasswordsBelongingToCategory(int index) const;

    [[nodiscard]] std::vector<Password> getSortedVector(const std::vector<int> &sortParameters) const;

    [[nodiscard]] bool isPasswordAlreadyUsed(const std::string &password) const;
};


#endif //PASSWORDMANAGER_PASSWORDMANAGER_H
