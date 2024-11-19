//
// Created by krzys on 14.05.2023.
//

#ifndef PASSWORDMANAGER_USERINTERFACE_H
#define PASSWORDMANAGER_USERINTERFACE_H

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include "Password.h"
#include "FileManager.h"

/**
 * @brief Funkcja wyświetlająca komunikat powitalny na konsoli
 */
void displayWelcome();

/**
 * Wyświetla na konsoli menu początkowe, które prezentuje dwie opcje, pozwalające
 * na określenie lokalizacji pliku z hasłami (nie odpowiada za sam wybór, tylko wyświetlanie)
 */
void displayFileMenu();

/**
 * \brief Funkcja wyświetlająca na konsoli ścieżki do plików, podane jako argument
 * @param path - vector, zawierający ścieżki do plików, które mają zostać wyświetlone
 */
void displayGivenFiles(const std::vector<std::filesystem::path> &path);

/**
 * @brief Funkcja wyświetlająca główne menu wyboru
 */
void displayMainMenu();

/**
 * @brief Wyświetla na konsoli, podaną jako argument, prośbę skierowaną do użytkownika na kolor biały
 * @param request - tekst prośby kierowanej przez program do użytkownika
 */
void displayRequest(const std::string &request);

/**
 * @brief Wyświetla na zielono podaną jako argument wiadomość
 * @param message - wiadomość, która zostanie wyświetlona na konsoli na kolor zielony
 */
void displaySuccess(const std::string &message);

/**
 * @brief Pobiera pojedyńczą linię od użytkownika i jednocześnie pilnuje
 * aby nie zawierała ona separatora, ustalonego w klasie FileManager
 * @return Wartość podaną przez użytkownika jako std::string
 */
std::string getStringDataFromUser();

/**
 * @brief wyświetla hasła z vector'a podanego jako argument
 *
 * Wyświetla hasła z vector'a podanego jako argument
 *
 * @param passwords - vector z hasłami, które mają zostać wyświetlone
 */
void displayPasswords(const std::vector<Password> &passwords);

/**
 *
 * Wyświetla hasła z vector'a podanego jako argument, a następnie czeka,
 * aż użytkownik kliknie ENTER
 *
 * @param passwords - vector z hasłami, które mają zostać wyświetlone
 */
void displayPasswordsWithEnter(const std::vector<Password> &passwords);

/**
 * @brief Wyświetla kategorie z vector'a podanego jako argument
 * @param categories - vector z kategoriami, które mają zostać wyświetlone
 */
void displayCategoriesToChoose(const std::vector<std::string>& categories);

/**
 * @brief Wyświetla na czerwono tekst, przekazany jako argument
 * @param message - wiadomość, która ma zostać wyświetlona
 */
void displayError(const std::string &message);

/**
 * @brief Wyświetla na czerwono komunikat o tym, że wprowadzona przez użytkownika
 * wartość jest niepoprawna
 */
void displayIncorrectInput();

/**
 * @brief Wyświetla na konsoli wiadomość podaną jako argument, bez formatowania wyświetlanego tekstu
 * @param message - wiadomość, która ma zostać wyświetlona
 */
void displayDefaultMessage(const std::string &message);

/**
 * @brief Wyświetla parametry, po których potem możliwe będzie sortowanie
 */
void displaySortParameters();

#endif //PASSWORDMANAGER_USERINTERFACE_H
