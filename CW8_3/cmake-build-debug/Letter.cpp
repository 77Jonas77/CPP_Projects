//
// Created by Jonasz Sójka on 11/05/2023.
//

#include "Letter.h"

Letter::Letter(const char* x) {
    int i=0;
    while(x[i] != '\0'){
        if(x[i]>='a' && x[i]<='z'){
            Letter::letters[x[i]-'a']++;
        }
        else if(x[i]>='A' && x[i]<='Z')
            Letter::letters[x[i]-'A']++;
        i++;
    }
}

Letter::Letter(std::string y) {
    for(int i=0;i<y.size(); i++){
        Letter::letters[y[i]-'a']++;
    }
}

char Letter::getMostFrequent() {
    int max=0;
    char maxe;
    for(int i=0;i<25; i++){
        if(max<Letter::letters[i]){
            max=Letter::letters[i];
            maxe=(char)(Letter::letters[i]+'a');
        }
    }
    return maxe;
}

int Letter::numOfDifferent() {
    int diff=0;

    for(int i=0;i<25;i++){
        if(Letter::letters[i]!=0)
            diff++;
    }
    return diff;
}

void Letter::printFrequencies() {
    for(int i=25;i>0;i--){
        for(int j=0;j<25;j++){
            std::cout << (Letter::letters[j]>i ? '*': ' ');
        }
        std::cout << std::endl;
    }
}