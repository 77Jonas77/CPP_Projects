//
// Created by Jonasz Sójka on 14/05/2023.
//

#ifndef PROJEKT_C___CRYPTINGMANAGER_H
#define PROJEKT_C___CRYPTINGMANAGER_H


#include <string>
/**
 * @class CryptingManager Klasa odpowiadaca szyfrowanie i odszyfrowanie hasel z wykorzystaniem klucza
 */
class CryptingManager {
public:

/**
 * Metoda majaca na celu zaszyfrowanie danych wedlug klucza
 * @param data dane, ktore maja byc zaszyfrowane
 * @param key klucz wedlug ktorego maja byc zaszyfrowane dane
 * @return zaszyfrowane dane, ktore wprowadzimy, szyfrujac sie kluczem
 */
    static std::string encryptData(const std::string& data, std::string key);
/**
 * Metoda majaca na celu odszyfrowanie danych wedlug klucza
 * @param encryptedData zaszyfrowane dane, ktore beda odszyfrowane
 * @param key klucz wedlug ktorego maja byc zaszyfrowane dane
 * @return odszyfrowane dane, ktore wprowadzimy, podslugujac sie kluczem
 */
    static std::string decryptData(const std::string& encryptedData, std::string key);
};


#endif //PROJEKT_C___CRYPTINGMANAGER_H
