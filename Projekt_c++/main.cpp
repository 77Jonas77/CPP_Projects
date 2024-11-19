#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>
#include "cmake-build-debug/PasswordManagerProgram.h"
#include "cmake-build-debug/PasswordManager.h"
#include "cmake-build-debug/CommunicationPanel.h"
#include "cmake-build-debug/CommunicationInterface.h"
#include "cmake-build-debug/CryptingManager.h"
#include "cmake-build-debug/FileManager.h"
#include "cmake-build-debug/Password.h"
#include "cmake-build-debug/SafetyChecker.h"
#include "cmake-build-debug/UsefulMethods.h"

//TO JEST PROJEKT MAC-owy
int main() {
    auto program = PasswordManagerProgram(new CommunicationPanel);
    program.chooseFileEntry();
    return 0;
}
