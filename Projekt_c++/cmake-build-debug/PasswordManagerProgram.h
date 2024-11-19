//
// Created by Jonasz Sójka on 15/05/2023.
//

#ifndef PROJEKT_C___PASSWORDMANAGERPROGRAM_H
#define PROJEKT_C___PASSWORDMANAGERPROGRAM_H

#include "PasswordManager.h"

/**
 * @class PasswordManagerProgram Klasa odpowiadajaca za przebieg programu (Wszystko zebrane i uporzadkowane)
 */
class PasswordManagerProgram {
private:
    CommunicationInterface* CI;
public:

    explicit PasswordManagerProgram(CommunicationInterface*);

    /**
     * Metoda odpowiadajaca za czesc programu, w ktorej znajduja sie wszystkie narzedzia i ich dzialanie + interakcja z uzytkownikiem
     */
    void chooseAvailableTool(PasswordManager&);

    /**
     * Metoda odpowiadajaca za poprawna kolejnosc/ dzialanie calego programu
     */
    void chooseFileEntry();
};


#endif //PROJEKT_C___PASSWORDMANAGERPROGRAM_H
