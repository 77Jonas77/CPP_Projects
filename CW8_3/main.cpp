#include <iostream>
#include "cmake-build-debug/Letter.h"

int main() {
    const char *text =
            "To be, or not to be- that is the questiona\n:" "Whether 'tis nobler in the mind to suffer\n" "The slings and arrows of outrageous fortune\n"
            "Or to take arms against a sea of troubles,\n"
            "And by opposing end them.";
    Letter lett(text);
    std::cout << "Most frequent letter: "
              << lett.getMostFrequent() << std::endl;
    std::cout << "Number of different letters: "
              << lett.numOfDifferent() << std::endl;
    std::cout << "Frequency table of all letters:\n";
    std::cout << std::endl;
    lett.printFrequencies();
}