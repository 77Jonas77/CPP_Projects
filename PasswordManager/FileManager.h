//
// Created by krzys on 14.05.2023.
//

#ifndef PASSWORDMANAGER_FILEMANAGER_H
#define PASSWORDMANAGER_FILEMANAGER_H

#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>
#include <set>
#include "UserInterface.h"
#include "Utilities.h"
#include "Encryptor.h"

class FileManager {
    static const int TS1LINE;
    static const int TS2LINE;
    static const int TS3LINE;
    static const std::filesystem::path CATEGORY_PATH;
    static const std::filesystem::path C_MAKE_CACHE_PATH;

    std::filesystem::path filePath;
    std::string secondTimestamp;
    std::string minuteTimestamp;
    std::string hourTimestamp;
    std::vector<std::string> currentFileState;

public:
    static const char SEPARATOR;

    /**
     * Metoda ustawiająca ścieżkę do pliku danego obiektu klasy FileManager, na tę podaną jako argument
     * @param path - nowa ścieżka do pliku
     */
    void setFilePath(const std::filesystem::path &path);

    /**
     *
     * @return Zwraca obecny stan pliku, przechowywany jako pole obiektowe
     */
    [[nodiscard]] const std::vector<std::string> &getCurrentFileState() const;

    /**
     * @brief Pobiera dane z pliku
     *
     * Pobiera dane z pliku, będącego określonym przez pole obiektowe, a następnie odczytuje z niego
     * całe linie i dodaje je do vector'a opisującego bierzący stan pliku, jednocześnie usuwając z nich timestamp'y
     */
    void downloadDataFromFile();

    /**
     * @brief Odczytuje bieżący czas systemowy i zapisuje go do pól obiektowych
     * @param time - bieżący czas systemowy
     */
    void saveAttemptedReadTimestamp(time_t time);

    /**
     * @brief Metoda zapisująca linie do pliku
     *
     * Metoda zapisuje podane jako pierwszy argument linie do pliku, określonego przez pole obiektowe
     * (w zależności od drugiego argumentu, np. czyści ten plik, czy też dopisuje do niego nowe linie na jego koniec)
     *
     * @param lines - linie które mają zostać zapisane, bądź dopisane do pliku (w zależności od drugiego argumentu)
     * @param mode - określa tryb, w jakim otwarty ma zostać plik
     */
    void saveLinesToFile(const std::vector<std::string> &lines, std::ios_base::openmode mode) const;

    /**
     * @brief Usuwa z pliku linie o indeksach zawartych w vectorze podanym jako argument
     * @param linesToDelete - vector z indeksami linii, które mają zostać usunięte z pliku
     */
    void deletePasswords(const std::set<int> &linesToDelete);

    /**
     * @brief Odświeża timestamp pliku oraz zapisuje ponownie całą jego zawartość
     *
     * Metoda dodająca odpowiedni timestamp do pliku i zapisująca ponownie wszystkie dane zawarte w polu
     * obiektowym, opisującym obecny stan pliku
     */
    void refreshTimestamp();

    /**
     * @brief Metoda zapisująca do pliku nowe hasło na pierwszą pustą w nim linię,
     * a następnie odświeżająca timestamp w pliku
     *
     * @param encryptedPassword - nowa linia, która ma zostać dodana do pliku
     */
    void saveNewEncryptedPasswordToFile(const std::string &encryptedPassword);

    /**
     * @brief Metoda edytująca podane hasło w pliku na nowe
     *
     * Metoda, która ma za zadanie odnaleźć i zastąpić starą linię hasła, tym nowym, zaszyfrowanym za pomocą podanego jako argument Encryptor'a
     *
     * @param oldLine - odszyfrowana, obecnie znajdująca się w pliku linia z hasłem
     * @param newLine - niezaszyfrowana linia z hasłem, która ma zostać zaszyfrowana i dodana do pliku
     * @param encryptor - obiekt klasy Encryptor, będący 'maszyną szyfrującą'
     */
    void editPasswordInFile(const std::string& oldLine, const std::string& newLine, const Encryptor& encryptor);

    /**
     * @brief Metoda zapisująca kategorię do pliku
     *
     * Statyczna metoda, zapisująca do pliku z kategoriami wartości zawarte w podanym jako argument wektorze
     *
     * @param categories - vector zawierający std::string, będące kategoriami, które mają zostać zapisane
     */
    static void saveCategories(const std::vector<std::string> &categories);

    /**
     * @brief Metoda odczytująca znajdujące się w pliku kategorię
     *
     * Metoda odczytująca znajdujące się w pliku kategorię i zwracające vector wartości, które zostaną odczytane
     *
     * @return Zwraca vector zawierający odczytane i wciąż zaszyfrowane kategorie
     */
    static std::vector<std::string> readCategories();

    /**
     * @brief Metoda statyczna wyszukująca pliki, znajdujące się w podanym jako argument katalogu
     *
     * Metoda statyczna wyszukująca pliki, znajdujące się w podanym jako argument katalogu
     * i spełniające wymagania dla potencjalnego pliku z hasłami (wykluczany jest plik z kategoriami i CMakeCache,
     * a sam plik musi mieć rozszerzenie .txt)
     *
     * @param path - ścieżka do folderu, który będzie przeszukiwany
     * @return Zwraca vector ścieżek do plików, które spełniają podane wymagania
     */
    static std::vector<std::filesystem::path> getFilesFromDir(const std::filesystem::path &path);

    /**
     * @brief Sprawdza czy podana jako argument ścieżka do pliku, jest ścieżką do potencjalnego pliku z hasłami
     * (wykluczany jest plik z kategoriami i CMakeCache, a sam plik musi mieć rozszerzenie .txt)
     * @param path - ścieżka do pliku, który będzie badany
     * @return Zwraca true, jeśli plik spełnia wymagania lub false w przeciwnym wypadku
     */
    static bool isPathToTXT(const std::filesystem::path &path);

    /**
     * @brief Sprawdza czy podana jako argument linia, zawiera odpowiednią ilość separatorów,
     * aby mogła zostać uznana za potencjalne hasło
     * @param line - linia, która ma zostać sprawdzona pod kątem ilości separatorów hasła w niej zawartych
     * @return Zwraca true, gdy podana jako argument linia jest potencjalnie hasłem (zawiera odpowiednią ilość separatorów) lub false w przeciwnym przypadku
     */
    static bool isLinePossiblePassword(const std::string &line);

    /**
     * @brief Usuwa kategorię z pliku
     *
     * Usuwa podaną jako argument zaszyfrowaną kategorię z pliku z kategoriami
     *
     * @param encryptedCategory - zaszyfrowana kategoria, która ma zostać usunięta z pliku
     */
    static void deleteCategory(const std::string &encryptedCategory);
};


#endif //PASSWORDMANAGER_FILEMANAGER_H
