//
// Created by Jonasz Sójka on 14/05/2023.
//

#ifndef PROJEKT_C___FILEMANAGER_H
#define PROJEKT_C___FILEMANAGER_H

#include "fstream"
#include "filesystem"
#include "Password.h"

/**
 * @class FileManager Klasa odpowiadajaca za operacje zwiazne z plikiem
 */
class FileManager {
public:
    static const char separator = ';';
    std::fstream dataFile;
private:
    std::filesystem::path filePath;
    std::filesystem::path categoriesFilePath;
    std::string timestamp;
public:

    FileManager(const std::filesystem::path&);

/**
 * Metoda, ktora ma zapisywac jedna linie danych do pliku
 * @param line zaszyfrowana linia danych, ktora bedziemy chcieli zapisac w pliku
 * @param key klucz wedlug, ktorego bedziemy odszyfrowywac dane
 */
    void saveLineToFile(const std::string& line, std::string key);

/**
 * Metoda odpowiadajaca za zwrocenie wektora plikow, ktore moga byc naszymi plikami zrodlowymi (zaszyfrowanymi)
 * @param path folder z ktorego wypisujemy pasujace pliki
 * @return vector pasujacych plikow
 */
    static std::vector<std::filesystem::path> getFilesFromDirectory(const std::filesystem::path&, std::string key);

    const std::filesystem::path &getFilePath() const;

/**
 * Metoda sprawdzajaca czy dany plik moze byc naszym plikiem przechowujacym hasla
 * @param path sprawdzany plik
 * @return informacje czy jest czy nie
 */
    static bool isFileTxt(const std::filesystem::path&, std::string key);

    void setFilePath(const std::filesystem::path &filePath);

/**
 * Metoda, ktora ma na celu wczytanie kateogrii z pliku, w ktorym one sie znajduja
 * @param path sciezka do pliku, w ktorym znajduja sie zapisywane kategorie
 * @param key klucz wedlug ktorego te kategorie sa szyfrowane / sluzy do odszyfrowania tych nazw kategorii, ktore znajduja sie w plik
 * @return lista kategorii, ktora znajdywala sie w pliku
 */
    std::vector<std::string> loadCategories(const std::filesystem::path&,std::string key);

/**
 * Metoda majaca na celu poprawne wczytanie hasel z pliku, ktory poda uzytkownik
 * @param path sciezka, w ktorej znajduje sie plik z haslami
 * @param key klucz wedlug ktorego hasla sa odszyfrowywane
 * @return lista hasel, ktora byla w pliku
 */
    std::vector<Password> loadPasswords(const std::filesystem::path&, std::string key);

/**
 * Metoda majaca na celu nadpisanie calego pliku z haslami, zapisujac przy tym timestampy
 * @param passwords lista hasel, ktora chcemy wprowadzic do pliku
 * @param key klucz wedlug ktorego chcemy zaszyfrowac ta liste hasel
 */
    void overwriteFileWithPasswords(const std::vector<Password>& passwords, std::string key);

/**
 * Metoda sluzaca do nadpisania calego pliku z kategoriami
 * @param categoryList lista kategorii, ktora bedziemy chcieli wprowadzic do pliku
 * @param key klucz wedlug ktorego bedziemy szyfrowac ta liste kategorii
 */
    void overwriteFileWithCategories(const std::vector<std::string>& categoryList, std::string key);

/**
 * Metoda, ktora odswieza (wprowdzajac aktualna godzine, minute, sekunde) pole obiektowe timestamp
 */
    void refreshTimestamp();

    const std::filesystem::path &getCategoriesFilePath() const;

    void setCategoriesFilePath(const std::filesystem::path &categoriesFilePath);

/**
 * Metoda sprawdzajaca czy podany plik spelnia warunki bycia plikiem zrodlowym (plikiem dla hasel), sprawdza czesc odpowiedzialna glownie za zawartosc pliku
 * @param path sciezka do pliku, ktory bedzie sprawdzany
 * @param key klucz wedlug ktorego bedziemy odszyfrowywac dane znajdujace sie w pliku
 * @return informacja czy plik spelnia warunki
 */
    static bool isFileValid(const std::filesystem::path &path, std::string key);

    const std::string &getTimestamp() const;

    void setTimestamp(const std::string &timestamp);

    ~FileManager()
    {
        if (dataFile.is_open())
        {
            dataFile.close();
        }
    }
};


#endif //PROJEKT_C___FILEMANAGER_H
