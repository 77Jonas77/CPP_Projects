//
// Created by krzys on 16.05.2023.
//

#ifndef PASSWORDMANAGER_PROGRAM_H
#define PASSWORDMANAGER_PROGRAM_H

#include <set>
#include "PasswordManager.h"
#include "FileManager.h"
#include "UserInterface.h"
#include "Utilities.h"
#include "Password.h"

class Program {
    PasswordManager passwordManager;
    FileManager fileManager;

public:
    /**
     * @brief Tworzy obiekt klasy Program i rozpoczyna wstępne działanie programu
     *
     * Konstruktor tworzący obiekt klasy Program, a następnie pozwalający użytkownikowi na określenie
     * ścieżki do pliku z hasłami, odkodowujący go według podanego przez niego klucza, a na końcu
     * odświeżający timestamp tego działania
     *
     */
    Program();

    /**
     * @brief Główna metoda działania programu
     *
     * Metoda, która wyświetla główne menu programu i poprzez interakcję z użytkownikiem
     * podejmuje odpowiednie działania, poprzez wywołania innych metod
     */
    void startProgram();

    /**
     * @brief Metoda odpowiadająca za mechanizm wyszukiwania haseł
     *
     * Metoda pobiera od użytkownika wartości z jakich ma składać się hasło, a następnie
     * pobiera vector haseł spełniających podane warunki oraz wyświetlające je, a jeśli
     * nie znaleziono takich haseł, powiadamia o tym użytkownika
     */
    void lookUpPasswords();

    /**
     * @brief Metoda odpowiadająca za usuwanie haseł z programu oraz z pliku
     *
     * Metoda usuwająca hasła z programu oraz z pliku, określone przez zbiór indeksów haseł, przekazany jako argument.
     * Przed usunięciem haseł wysyła komunikat do użytkownika, czy jest pewien swoich działań.
     *
     * @param indexes - set indeksów haseł, które należy usunąć
     */
    void deletePasswords(const std::set<int> &indexes);

    /**
     * @brief Metoda odpowiadająca za mechanizm dodawania nowego hasła
     *
     * Metoda odpowiadająca za mechanizm dodawania nowego hasła. Pobiera od użytkownika wartości, z których
     * składać się będzie nowe hasło. Metoda ta zapewnia, że nie zostanie dodane nowe hasło,
     * które jest już gdzieś indziej wykorzystane. Daje też możliwość automatycznego wygenerowania hasła.
     */
    void addPassword();

    /**
     * @brief Metoda odpowiadająca za dodawanie nowej kategorii
     *
     * Metoda ta odpowiada za dodawanie nowej kategorii o nazwie podanej przez użytkownika.
     * Jednocześnie zapewnia ona, że dana nazwa kategorii, nie została już wcześniej wykorzystana.
     */
    void addNewCategory();

    /**
     * @brief Metoda odpowiadająca za edycję istniejącego już hasła
     *
     * Metoda pobiera informację od użytkownika, które pole hasła chce on edytować, a następnie umożliwia mu jego edycję.
     * @attention W przypadku, gdy edytowane jest hasło, wywoływana jest inna metoda, która zapewnia wszelkie potrzebne walidacje.
     * @attention W przypadku, gdy edytowana jest kategoria, również wywoływana jest inna metoda z wszelkimi koniecznymi walidacjami.
     */
    void editPassword();

    /**
     * @brief Metoda odpowiedzialna za utworzenie nowego hasła
     *
     * Metoda odpowiedzialna za utworzenie nowego hasła. Daje użytkownikowi wybór, czy chce,
     * aby hasło zostało automatycznie wygenerowane, czy też woli wpisać je sam. W obu przypadkach
     * zapewnia, że hasło nie będzie wykorzystane już w jakimś innym rekordzie.
     *
     * @return Zwraca std::string z nowym hasłem, wybranym i zaakceptowanym przez użytkownika
     */
    [[nodiscard]] std::string getNewPassword() const;

    /**
     * @brief Metoda odpowiedzialna za wybranie kategorii do nowego hasła
     *
     * Metoda odpowiedzialna za wybranie kategorii do nowego hasła.
     * Daje użytkownikowi listę do wyboru istniejących kategorii, bądź oferuje mu możliwość
     * utworzenia nowej kategorii.
     *
     * @return Zwraca std::string z kategorią wybraną, bądź utworzoną przez użytkownika
     */
    std::string getNewCategory();

    /**
     * @brief Metoda odpowiedzialna za usunięcie kategorii wraz z wszystkimi jej hasłami
     *
     * Metoda odpowiedzialna za usunięcie kategorii wskazanej przez podany argument oraz wszystkich
     * jej haseł. Przed takim działaniem w odpowiedni sposób powiadamia użytkownika o konsekwencj jego
     * działania i czeka na jego aprobatę.
     *
     * @param index - wartość określająca indeks kategorii w vectorze kategorii
     */
    void deleteCategory(int index);

    /**
     * @brief Metoda odpowiedzialna za funkcjonalność sortowania haseł
     *
     * Metoda, która pobiera z innej metody vector posortowanych haseł, a następnie wyświetla go
     * użytkownikowi i czeka.
     *
     * @param sortParameters - vector parametrów, według których sortowane będzie hasło
     */
    void sortPasswords(const std::vector<int> &sortParameters);

    /**
     * @brief Metoda określająca parametry sortowania haseł
     *
     * Metoda pobiera od użytkownika wartości, wedle których chce on sortować hasła.
     * Kolejność podania parametrów przez użytkownika ma znaczenie, gdyż najpierw sortowanie odbywa
     * się po pierwszym podanym parametrze, następnie po drugim itd.
     *
     * @return Zwraca vector indeksów parametrów, po których odbywać się będzie sortowanie
     */
    [[nodiscard]] std::vector<int> getSortParameters() const;

    /**
     * @brief Metoda pozwalająca użytkownikowi określić, która kategoria ma zostać usunięta
     *
     * @return Zwraca indeks kategorii, wybranej przez użytkownika jako ta do usunięcia
     */
    int getCategoryToDeleteIndex();

    /**
     * @brief Metoda pozwalająca użytkownikowi określić, które hasła chce on usunąć
     *
     * Metoda pozwala określić użytkownikowi, które hasła chce on usunąć, w sposób taki,
     * aby użytkownik mógł wskazać wiele haseł jednocześnie.
     *
     * @return Zwraca set indeksów haseł, określonych przez użytkownika jako do usunięcia
     */
    std::set<int> getIndexesOfPasswordsToRemove();

    /**
     * @brief Metoda odpowiedzialna za określenie ścieżki, do pliku z hasłami
     *
     * Metoda pozwala użytkownikowi określić ścieżkę do pliku z hasłami.
     * Może on to zrobić poprzez określenie bezpośredniej ścieżki do pliku, bądź wybranie
     * jednego z dostępnych plików .txt w katalogu 'cmake-build-debug' projektu
     *
     * @return Zwraca ścieżkę do pliku, który będzie traktowany jako plik z hasłami
     */
    static std::filesystem::path getPathToPasswordFile();

    /**
     * @brief Metoda określająca siłę hasła podanego jako argument
     *
     * Metoda określająca siłę hasła podanego jako argument. Sprawdza ilość dużych i małych liter oraz
     * znaków specjalnych i na podstawie ich ilości, jak i całkowitej długości hasła określa jego siłę
     * w skali od 1 do 4. Następnie tworzy odpowiedni komunikat dla użytkownika, który przeznaczony jest
     * do wyświetlenia.
     *
     * @param password - hasło, które będzie badane pod kątem jego siły
     * @return Zwraca std::string, który może zostać wyświetlony i mówi on o sile hasła, jednocześnie
     * stosując do tego kolorowanie tekstu na konsoli.
     */
    static std::string passwordStrength(const std::string &password);
};


#endif //PASSWORDMANAGER_PROGRAM_H
