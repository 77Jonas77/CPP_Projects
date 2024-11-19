//
// Created by Jonasz Sójka on 15/05/2023.
//

#ifndef PROJEKT_C___USEFULMETHODS_H
#define PROJEKT_C___USEFULMETHODS_H


#include <string>
#include <filesystem>

class UsefulMethods {
public:

/**
 * Metoda sprawdza czy podany napis reprezentuje liczba
 * @param str liczba w postaci napisu
 * @return informajca czy reprezentuje liczbe
 */
    static bool isNumber(const std::string& str);

/**
 * Metoda sprawdzajaca czy podana kategoria znajduje sie na liscie dostepnych/dodanych kategorii
 * @param category kategoria, ktora bedziemy sprawdzac
 * @param categoryList lista kategorii, ktora sa dostepne
 * @return czy lista zawiera podana kategorie
 */
    static bool categoryExists(std::string& category, std::vector<std::string>& categoryList);

/**
 * Metoda sprawdzajaca czy podana wartosc znajduje sie w dostarczonym vectorze
 * @param vec vector sciezek
 * @param value sciezka do pliku
 * @return informacja czy sciezka zawiera sie w vectorze sciezek
 */
    static bool containsValue(const std::vector<std::filesystem::path>& vec, std::string value);
/**
 * Metoda sprawdzajaca czy podany separator znajduje sie w dostarczonym napisie
 * @param separator szukany separator
 * @param value napis, w ktorym sprawdzamy czy podany separator wystepuje
 * @return informacja czy napis zawiera separator
 */
    static bool containsSeparator(const char, const std::string&);
};


#endif //PROJEKT_C___USEFULMETHODS_H
