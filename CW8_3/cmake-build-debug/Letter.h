//
// Created by Jonasz Sójka on 11/05/2023.
//

#ifndef CW8_3_LETTER_H
#define CW8_3_LETTER_H

#include <iostream>

class Letter {
    int letters[26]{0};
    public:
        Letter(std::string);
        Letter(const char*);
        char getMostFrequent();
        int numOfDifferent();
        void printFrequencies();
};


#endif //CW8_3_LETTER_H
