//
// Created by Jonasz Sójka on 14/05/2023.
//

#ifndef PROJEKT_C___SAFETYCHECKER_H
#define PROJEKT_C___SAFETYCHECKER_H

#include <string>
#include <fstream>
#include <string>

class SafetyChecker {

public:

/**
 * Metoda sprawdzajaca jak bezpieczne jest haslo na podstawie kilku kryteriow
 * @param password sprawdzane haslo
 * @return informacja o poziomie bezpieczenstwa hasla
 */
    static std::string howSafeIsPassword(const std::string& password);

/**
 * metoda sprawdzajaca czy haslo bylo juz wczesniej wykorzystane
 * @param password nowe haslo
 * @param passwordList lista rekordow ktore znajduja sie w pliku
 * @return
 */
    static bool wasUsedBefore(std::string& password,const std::vector<std::string>& passwordList);
};


#endif //PROJEKT_C___SAFETYCHECKER_H
