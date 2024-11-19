//
// Created by krzys on 16.05.2023.
//

#ifndef PASSWORDMANAGER_UTILITIES_H
#define PASSWORDMANAGER_UTILITIES_H

#include <string>
#include <ctime>
#include <vector>
#include <algorithm>

/**
 * Funkcja sprawdzająca czy podany jako argument std::string jest jakąś liczbą
 * @param str - std::string, który będzie sprawdzany czy jest liczbą
 * @return Zwraca true gdy podany std::string jest liczbą lub false w przeciwnym wypadku
 */
bool isNumber(const std::string &str);

/**
 * Funkcja sprawdzająca czy podany jako argument char jest liczbą
 * @param ch - znak, który będzie sprawdzany czy jest liczbą
 * @return Zwraca true gdy podany znak jest liczbą lub false w przeciwnym wypadku
 */
bool isNumber(const char &ch);

/**
 * Funkcja sprawdzająca, czy podany jako argument std::string zawiera jakieś znaki białe
 * @param str - std::string, który będzie sprawdzany czy zawiera jakieś znaki białe
 * @return Zwraca true, gdy std::string zawiera jakieś znaki białe lub false w przeciwnym wypadku
 */
bool doesStringContainWhitespace(const std::string &str);

/**
 * Zlicza ile razy dany character podany jako pierwszy argument występuje w tekście podanym jako pierwszy argument
 * @param text - text, w którym zliczana będzie ilość konkretnych znaków
 * @param character - character, którego ilość wystąpień chcemy zliczyć
 * @return Zwraca ilość wystąpień danego znaku w podanym tekście
 */
int countCharAppInString(const std::string &text, char character);

/**
 * @brief Metoda generująca nowe hasło
 *
 * Metoda generującą nowe hasło, biorąc pod uwagę podane jako argumenty zmienne
 * @param size - rozmiar hasła, które będzie generowane
 * @param upperLowerCase - określa, czy generowane hasło ma zawierać małe i duże litery
 * @param specialCharacters - określa, czy generowane hasło ma zawierać znaki specjalne
 * @return Zwraca nowo wygenerowane hasło
 */
std::string generatePassword(int size, bool upperLowerCase, bool specialCharacters);

/**
 * Modyfikuje podany jako argument vector std::string, tak , aby składał się on  z samych małych liter
 * @param vec - vector zawierający wartości std::string, które mają zostać zmodyfikowane
 * @return Zwraca ten sam vector, który został podany jako argument, ale wszystkie jego elementy składają się z małych liter
 */
std::vector<std::string> toLowercase(std::vector<std::string> &vec);

#endif //PASSWORDMANAGER_UTILITIES_H
