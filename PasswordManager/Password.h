//
// Created by krzys on 14.05.2023.
//

#ifndef PASSWORDMANAGER_PASSWORD_H
#define PASSWORDMANAGER_PASSWORD_H

#include <string>
#include <vector>


class Password {
    std::string name;
    std::string password;
    std::string category;
    std::string webpage;
    std::string login;

public:
    /**
     * @brief Tworzy nowy obiekt klasy password, opisujący pojedynczy rekord z danymi hasła
     * @param name - nazwa własna tworzonego hasła
     * @param password - hasło tworzonego hasła
     * @param category - kategoria tworzonego hasła
     * @param webpage - strona www tworzonego hasła
     * @param login - login tworzonego hasło
     */
    Password(const std::string &name, const std::string &password, const std::string &category,
             const std::string &webpage, const std::string &login);

    /**
     * @return Zwraca nazwę własną hasła
     */
    [[nodiscard]] const std::string &getName() const;

    /**
     * @brief Ustawia nazwę hasła na nową, podaną jako argument
     * @param name - nowa nazwa własna hasła
     */
    void setName(const std::string &name);

    /**
     *
     * @return Zwraca hasło danego obiektu klasy Password
     */
    [[nodiscard]] const std::string &getPassword() const;

    /**
     * @brief Ustawia hasło danego obiektu klasy Password na nowe, podane jako argument
     * @param password - nowe hasło, które ma zostać ustawione
     */
    void setPassword(const std::string &password);

    /**
     *
     * @return Zwraca kategorię hasła
     */
    [[nodiscard]] const std::string &getCategory() const;

    /**
     * @brief ustawia kategorię na nową, podaną jako argument
     * @param category - nowa kategoria, która ma zostać ustawiona
     */
    void setCategory(const std::string &category);

    /**
     *
     * @return Zwraca stronę www hasła
     */
    [[nodiscard]] const std::string &getWebpage() const;

    /**
     * @brief Ustawia stronę www hasła na nową, podaną jako argument
     * @param webpage - nowa strona www hasła
     */
    void setWebpage(const std::string &webpage);

    /**
     *
     * @return Zwraca login hasła
     */
    [[nodiscard]] const std::string &getLogin() const;

    /**
     * Ustawia login hasła na nowy, podany jako argument
     * @param login - nowy login hasła
     */
    void setLogin(const std::string &login);

    /**
     * @brief Składa pola obiektowa obiektu do jednego vector'a std::string
     * @return Vector std::string z poszczególnymi danymi hasła na kolejnych pozycjach
     */
    [[nodiscard]] std::vector<std::string> toVector() const;

    /**
     * @brief Przekształca hasło w jednego std::string, który może zostać zaszyfrowany i  zapisany do pliku
     * @param separator - separator stosowany w pliku do oddzielenia kolejnych danych
     * @return std::string złożony z poszczególnych pól hasła oddzielonych separatorami
     */
    [[nodiscard]] std::string toFileLine(char separator) const;

    /**
     * @brief Dopisuje do strumienia hasło, w sposób w jaki ma być ono wyświetlane na konsoli
     * @param ostream - strumień wyjściowy do którego chcemy przekazać hasło
     * @param password - hasło które ma zostać przekazane do strumienia
     * @return Referencja do strumienia podanego jako argument, ale po dopisaniu do niego hasła
     */
    friend std::ostream &operator<<(std::ostream &ostream, const Password &password);
};


#endif //PASSWORDMANAGER_PASSWORD_H
