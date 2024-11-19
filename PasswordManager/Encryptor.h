//
// Created by krzys on 14.05.2023.
//

#ifndef PASSWORDMANAGER_ENCRYPTOR_H
#define PASSWORDMANAGER_ENCRYPTOR_H

#include <string>

class Encryptor {
    std::string key;
    int sumOfKey;

public:
    Encryptor();

    /**
     * @brief Tworzy nowy obiekt typu Encryptor
     *
     * Konstruktor przyjmujący jako argument klucz, wedle którego szyfrowane i deszyfrowane
     * będą dane i ustawiający go jako klucz dla nowo tworzonego obiektu klasy Encryptor
     *
     * @param key - klucz wedle którego szyfrowane i deszyfrowane będą dane
     */
    Encryptor(const std::string &key);

    /**
     * @brief Szyfruje podany jako argument tekst
     *
     * Metoda, której zadaniem jest zaszyfrowanie podanego jako argument tekstu według
     * klucza zawartego w obiekcie, na rzecz którego wywoływana jest metoda
     *
     * @param text - tekst który ma zostać zaszyfrowany
     * @return zaszyfrowany tekst podany jako argument
     */
    [[nodiscard]] std::string encryptString(const std::string &text) const;

    /**
     * @brief Deszyfruje podany jako argument tekst
     *
     * Metoda, której zadaniem jest odszyfrowanie podanego jako argument tekstu według
     * klucza zawartego w obiekcie, na rzecz którego wywoływana jest metoda
     *
     * @param text - tekst który ma zostać odszyfrowany
     * @return odszyfrowany tekst podany jako argument
     */
    [[nodiscard]] std::string decipherString(const std::string &text) const;
};


#endif //PASSWORDMANAGER_ENCRYPTOR_H
