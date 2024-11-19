//
// Created by Jonasz Sójka on 14/05/2023.
//

#ifndef PROJEKT_C___COMMUNICATIONPANEL_H
#define PROJEKT_C___COMMUNICATIONPANEL_H

#include "CommunicationInterface.h"
#include <string>


/**
 * @class CommunicationPanel Klasa odpowiadajaca za komunikacje z uzytkownikiem w celu oddzielenia grafiki od logiki
 */
class CommunicationPanel : public CommunicationInterface {
public:

    /**
     * metoda, ktora wyswietla dowolny komunikat (do komunikacji z uzytkownikiem) na konsoli
     */
    void printCutomMessesage(std::string) const override;

    /**
     * metoda, wyswietlajaca wiadomosc wiadomosc, ktora ma na celu powitac uzytkownika
     */
    void printHelloMessesage() const override;

    /**
     * metoda wyswietlajaca wszystkie dostepne narzedzia w naszym menedzerze zadan
     */
    void printAvailableTools() const override;

    /**
     * metoda, ktora wyswietla komunikaty o ostrzezeniach i niepoprawnych inputach od uzytkownika
     */
    void printAlert(std::string) const override;

    /**
     * metoda, ktora wyswietla poprawne wyniki na podstawie poprawnych inputow
     */
    void printCorrectResult(std::string) const override;

    ~CommunicationPanel() override = default;
};


#endif //PROJEKT_C___COMMUNICATIONPANEL_H
