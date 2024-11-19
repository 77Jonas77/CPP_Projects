//
// Created by Jonasz Sójka on 15/05/2023.
//

#ifndef PROJEKT_C___PASSWORD_H
#define PROJEKT_C___PASSWORD_H

#include <string>

/**
 * @class Password Klasa odpowiadajaca za rekord informacjii o haslach (czyli o nazwie wlasnej, hasle i kategorii) oraz za zwiazane z haslem metody
 */
class Password {
private:
    std::string name;
    std::string passw;
    std::string cat;
    std::string www;
    std::string login;
public:
/**
 * Metoda, ktora wygeneruje haslo wedlug wprowadzonych parametrow
 * @param ifC parametr okreslajacy, czy mozemy uzyc duzych liter w generowanym hasle?
 * @param ifL parametr okreslajacy, czy mozemy uzyc malych liter w generowanym hasle?
 * @param ifS parametr okreslajacy, czy mozemy uzyc znakow specjalnych w generowanym hasle?
 * @param length parametr okreslajacy dlugosc hasla, ktore wygeneruje
 * @return Haslo, ktore zostalo wygenerowane wedlug wprowadzonych parametrow
 */
    static std::string generatePassword(bool ifC, bool ifL, bool ifS, int length);

    Password(std::string, std::string, std::string, std::string, std::string);

    const std::string &getName() const;

    void setName(const std::string &name);

    const std::string &getPassw() const;

    void setPassw(const std::string &passw);

    const std::string &getCat() const;

    void setCat(const std::string &cat);

    const std::string &getWww() const;

    void setWww(const std::string &www);

    const std::string &getLogin() const;

    void setLogin(const std::string &login);

/**
 * Metoda wyswietlajaca wszystkie informacje o hasle / rekordzie danych w pliku
 * @return
 */
    std::string toString() const;

/**
 * Metoda sluzaca do porownywania hasel, tzn jest wykorzystywana jako comparator miedzy 2 haslami nawet do 3 parametrow
 * @param p1 pierwsze haslo
 * @param p2 drugie haslo
 * @return informacje o tym, czy parametry p1 (rekordu/hasla) sa mniejsze alfabetycznie od p2
 */
    static bool comparePasswords(const Password& p1, const Password& p2);
};


#endif //PROJEKT_C___PASSWORD_H
