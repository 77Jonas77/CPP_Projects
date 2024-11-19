//
// Created by Jonasz Sójka on 14/05/2023.
//

#ifndef PROJEKT_C___COMMUNICATIONINTERFACE_H
#define PROJEKT_C___COMMUNICATIONINTERFACE_H

#include <string>

/**
 * @interface CommunicationInterface Klasa abstrakcyjna, ktora bedzie sluzyla jako Interfejs umozliwiajacy komunikacje z uzytkownikiem, majaca na celu rozdzielenie grafiki od logiki
 */

class CommunicationInterface {
public:
    /**
     * metoda, ktora bedzie przeciazana przez inna klase, wyswietlajac dostarczana wiadomosc
     */
    virtual void printCutomMessesage(std::string) const;

    /**
     * metoda, ktora bedzie wyswietlala na konsoli wiadomosc wystepujaca na poczatku/ komunikujaca sie z uzytkownikiem
     */
    virtual void printHelloMessesage() const;

    /**
     * metoda, ktora bedzie miala sluzyc w celu wyswietlenia wszystkich dostepnych narzedzi w naszym menedzerze
     */
    virtual void printAvailableTools() const;

    /**
     * metoda, ktora bedzie sluzyc alertowaniu o niepoprawnych inputach itp
     */
    virtual void printAlert(std::string) const;

    /**
     * metoda, ktora bedzie sluzyc do wyswietlania poprawnych wynikow (na podstawie poprawnych parametrow)
     */
    virtual void printCorrectResult(std::string) const;

    virtual ~CommunicationInterface();
};


#endif //PROJEKT_C___COMMUNICATIONINTERFACE_H
