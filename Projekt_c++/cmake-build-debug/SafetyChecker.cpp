//
// Created by Jonasz Sójka on 14/05/2023.
//

#include <iostream>
#include "SafetyChecker.h"
#include <string>

std::string SafetyChecker::howSafeIsPassword(const std::string& password) {
    bool hasLower = false;
    bool hasUpper = false;
    bool hasDigit = false;
    bool hasSpecial = false;

    int complexity = 0;
    for (char ch: password) {
        if (std::islower(ch)){
            hasLower = true;
            complexity++;
        }
        else if (std::isupper(ch)){
            hasUpper = true;
            complexity++;
        }
        else if (std::isdigit(ch)){
            hasDigit = true;
            complexity++;
        }
        else{
            hasSpecial = true;
            complexity++;
        }

    }

    // pytanie jak to sie ma w kontekscie generowanego hasla...
    if (password.length() < 8 || complexity<2) {
        return "\033[31mBardzo Slabe\033[0m\n";
    } else if (password.length() > 7 && complexity==4) {
        return "\033[42mBardzo Silne\033[0m\n";
    } else if(password.length() > 7 && complexity==3 && hasSpecial){
        return "\\033[36mSilne\033[0m\n";
    }else if(password.length() > 7 && complexity==2 && !hasSpecial && !hasDigit){
        return "\033[31;43mSlabe\033[0m";
    }else {
        return "\033[33mSrednie\033[0m";
    }
}

bool SafetyChecker::wasUsedBefore(std::string &password, const std::vector<std::string> &passwordList) {
    auto index = std::find(passwordList.begin(), passwordList.end(), password);
    if (index != passwordList.end()) {
        return true;
    } else {
        return false;
    }
}

