//
// Created by krzys on 16.05.2023.
//

#include "Program.h"

Program::Program() {
    displayWelcome();
    fileManager.setFilePath(getPathToPasswordFile());
    displayRequest("Enter the password to the file:");
    std::string keyToFile = getStringDataFromUser();
    fileManager.saveAttemptedReadTimestamp(time(nullptr));
    fileManager.downloadDataFromFile();
    passwordManager = PasswordManager(fileManager.getCurrentFileState(), keyToFile);
    fileManager.refreshTimestamp();
}

std::filesystem::path Program::getPathToPasswordFile() {
    while (true) {
        displayFileMenu();
        std::string input = getStringDataFromUser();
        int in;
        if (isNumber(input) && ((in = std::stoi(input)) == 1 || in == 2)) {
            if (in == 1) {
                auto files = FileManager::getFilesFromDir(std::filesystem::current_path());
                if (files.empty()) {
                    displayError("No files found in the current directory");
                } else {
                    displayGivenFiles(files);
                    input = getStringDataFromUser();
                    if (isNumber(input) && (in = std::stoi(input)) >= 1 && in <= files.size()) {
                        return files.at(in - 1);
                    } else displayIncorrectInput();
                }
            } else {
                displayRequest("Enter path to .txt file with passwords:");
                input = getStringDataFromUser();
                auto testPath = std::filesystem::path(input);
                if (FileManager::isPathToTXT(testPath)) {
                    return testPath;
                } else displayIncorrectInput();
            }
        } else displayIncorrectInput();
    }
}

void Program::startProgram() {
    bool working = true;
    while (working) {
        displayMainMenu();
        std::string input = getStringDataFromUser();
        if (isNumber(input) && !input.empty()) {
            int in = std::stoi(input);
            switch (in) {
                case 0: {
                    working = false;
                    std::vector<std::string> categoriesToSave;
                    for (const auto &cat: passwordManager.getCategories()) {
                        categoriesToSave.push_back(passwordManager.getEncryptor().encryptString(cat));
                    }
                    FileManager::saveCategories(categoriesToSave);
                    break;
                }
                case 1:
                    if (passwordManager.getPasswords().empty()) {
                        displayError("There are no passwords in file!");
                        break;
                    }
                    displayRequest("Passwords in the file:");
                    displayPasswordsWithEnter(passwordManager.getPasswords());
                    break;
                case 2:
                    if (passwordManager.getPasswords().empty())
                        displayError("There are no passwords in the file!");
                    else {
                        lookUpPasswords();
                    }
                    break;
                case 3:
                    if (passwordManager.getPasswords().empty())
                        displayError("There are no passwords in the file!");
                    else {
                        sortPasswords(getSortParameters());
                    }
                    break;
                case 4:
                    addPassword();
                    break;
                case 5:
                    if (passwordManager.getPasswords().empty())
                        displayError("There are no passwords in the file!");
                    else {
                        editPassword();
                    }
                    break;
                case 6:
                    if (passwordManager.getPasswords().empty())
                        displayError("There are no passwords in the file!");
                    else {
                        deletePasswords(getIndexesOfPasswordsToRemove());
                    }
                    break;
                case 7:
                    addNewCategory();
                    break;
                case 8:
                    if (passwordManager.getCategories().empty())
                        displayError("There is currently no category existing.");
                    else {
                        deleteCategory(getCategoryToDeleteIndex());
                    }
                    break;
                default:
                    displayIncorrectInput();
            }
        } else displayIncorrectInput();
    }
}

void Program::addPassword() {
    std::vector<std::string> passData;

    // Dodawanie nazwy
    displayRequest("Enter the password name: (press '0' to cancel)");
    std::string input = getStringDataFromUser();

    if (input == "0")
        return;

    while (input.empty()) {
        displayError("Password name cannot be an empty field!");
        displayRequest("Enter the password name");
        input = getStringDataFromUser();
    }

    passData.push_back(input);

    passData.push_back(getNewPassword());

    // Dodawanie kategorii
    passData.push_back(getNewCategory());

    // Dodawanie witryny
    displayRequest("*Enter a webpage for your password (press ENTER to skip)");
    input = getStringDataFromUser();
    passData.push_back(input);

    // Dodawanie loginu
    displayRequest("*Enter a login for your password (press ENTER to skip)");
    input = getStringDataFromUser();
    passData.push_back(input);

    passwordManager.addPassword(passData, fileManager);
}

std::string Program::passwordStrength(const std::string &password) {
    std::string message;
    auto size = password.size();
    int lCase = 0;
    int uCase = 0;
    int specialCount = 0;
    int strength = 0;
    std::string color = (size >= 8 ? "\033[32m" : "\033[31m");
    message += "\n - Number of characters: " + color + std::to_string(size) + "\033[0m";

    for (char ch: password) {
        if (ch >= 'A' && ch <= 'Z')
            uCase++;
        else if (ch >= 'a' && ch <= 'z')
            lCase++;
        else if (!(ch >= '0' && ch <= '9'))
            specialCount++;
    }

    color = ((uCase >= 2 && lCase >= 2) ? "\033[32m" : "\033[31m");
    message += "\n - Lower and upper case letters: " + color +
               "lowercase(" + std::to_string(lCase) + "); " +
               "uppercase(" + std::to_string(uCase) + ")" + "\033[0m";
    color = (specialCount >= 2 ? "\033[32m" : "\033[31m");
    message += "\n - Special characters: " + color + std::to_string(specialCount) + "\033[0m";

    if (size >= 8)
        strength++;

    if (lCase > 2 && uCase > 2)
        strength++;

    if (specialCount >= 2)
        strength++;

    switch (strength) {
        case 0 :
            color = "\033[31m";
            message += color + "\nGiven password is very weak";
            break;
        case 1 :
            color = "\033[33m";
            message += color + "\nGiven password is weak";
            break;
        case 2 :
            color = "\033[92m";
            message += color + "\nGiven password is pretty good";
            break;
        case 3 :
            color = "\033[32m";
            message += color + "\nGiven password is very strong";
            break;
        default:
            color = "\033[35m";
            message += color + "\nI could not analyse given password";
    }

    message += "\033[0m";

    return message;
}

void Program::addNewCategory() {
    bool added = false;
    while (!added) {
        displayRequest("How would you like to name the new category? (press '0' to cancel)");
        std::string catName = getStringDataFromUser();

        if (catName == "0")
            return;

        if (!passwordManager.doesCategoryAlreadyExist(catName)) {
            passwordManager.addCategory(catName);
            FileManager::saveCategories(passwordManager.getCategories());
            added = true;
        } else displayError("This category already exists");
    }
}

void Program::lookUpPasswords() {
    std::vector<std::string> parameters;

    displayRequest("What should the password name be (press ENTER if any)?");
    std::string lookingForName = getStringDataFromUser();
    parameters.push_back(lookingForName);

    displayRequest("What should the password be (press ENTER if any)?");
    std::string lookingForPassword = getStringDataFromUser();
    parameters.push_back(lookingForPassword);

    displayRequest("What should the category be (press ENTER if any)?");
    displayCategoriesToChoose(passwordManager.getCategories());
    std::string input = getStringDataFromUser();
    bool looking = true;

    // Szukanie po kategoriach
    while (looking) {
        if (input.empty()) {
            parameters.push_back(input);
            looking = false;
        } else if (isNumber(input)) {
            int in = std::stoi(input);
            if (in >= 1 && in <= passwordManager.getCategories().size()) {
                parameters.push_back(passwordManager.getCategories().at(in - 1));
                looking = false;
            } else displayIncorrectInput();
        } else displayIncorrectInput();
    }

    displayRequest("What should the website be (press ENTER if any)?");
    std::string lookingForWebsite = getStringDataFromUser();
    parameters.push_back(lookingForWebsite);

    displayRequest("What should the login be (press ENTER if any)?");
    std::string lookingForLogin = getStringDataFromUser();
    parameters.push_back(lookingForLogin);

    auto lookedUp = passwordManager.searchPassword(parameters);

    if (lookedUp.empty()) displayError("I have found nothing matching the given pattern!");
    else {
        displayRequest("I have found " + std::to_string(lookedUp.size()) + " passwords matching the given pattern!");
        displayPasswordsWithEnter(lookedUp);
    }
}

void Program::deletePasswords(const std::set<int> &indexes) {
    if (!indexes.empty()) {
        std::string input = "no";
        do {
            if (input != "no") displayIncorrectInput();
            displayError("WARNING! You are trying to remove " + std::to_string(indexes.size()) +
                         " passwords. Are you sure you want to proceed? (yes/no)");
            input = getStringDataFromUser();
        } while (input != "no" && input != "yes");

        if (input == "no")
            return;

        fileManager.deletePasswords(indexes);

        for (auto index: indexes)
            passwordManager.removePassword(index);
    }
}

std::set<int> Program::getIndexesOfPasswordsToRemove() {
    displayRequest("Which passwords would you like to delete? (i.e. '1' or '1 3 4')");
    displayPasswords(passwordManager.getPasswords());
    std::string input = getStringDataFromUser();
    std::set<int> passNumbersToRemove;
    bool linesSelected = false;
    while (!linesSelected) {
        if (isNumber(input)) {
            int in = std::stoi(input);
            if (in >= 1 && in <= passwordManager.getPasswords().size()) {
                passNumbersToRemove.insert(in - 1);
                linesSelected = true;
            } else displayIncorrectInput();
        } else {
            int lineNumber = 0;
            for (auto ch: input) {
                if (ch == ' ') {
                    if (lineNumber >= 1 && lineNumber <= passwordManager.getPasswords().size()) {
                        passNumbersToRemove.insert(lineNumber - 1);
                    } else {
                        displayIncorrectInput();
                        break;
                    }
                    lineNumber = 0;
                } else if (isNumber(ch)) {
                    lineNumber *= 10;
                    lineNumber += (ch - '0');
                } else {
                    displayIncorrectInput();
                    break;
                }
            }
            if (lineNumber >= 1 && lineNumber <= passwordManager.getPasswords().size()) {
                passNumbersToRemove.insert(lineNumber - 1);
                linesSelected = true;
            } else {
                displayIncorrectInput();
            }
        }
        if (!linesSelected) {
            displayRequest("Which passwords would you like to delete? (i.e. '1' or '1 3 4')");
            displayPasswords(passwordManager.getPasswords());
            input = getStringDataFromUser();
        }
    }
    return passNumbersToRemove;
}

void Program::deleteCategory(int index) {
    auto passToDeleteIndexes = passwordManager.getPasswordsBelongingToCategory(index);

    std::string input = "no";
    do {
        if (input != "no") displayIncorrectInput();
        displayError(
                "WARNING! You are trying to remove category " + passwordManager.getCategories().at(index) + " and " +
                std::to_string(passToDeleteIndexes.size()) +
                " passwords belonging to it.\nAre you sure you want to proceed? (yes/no)");
        input = getStringDataFromUser();
    } while (input != "no" && input != "yes");

    if (input == "no")
        return;

    deletePasswords(passToDeleteIndexes);
    FileManager::deleteCategory(
            passwordManager.getEncryptor().encryptString(passwordManager.getCategories().at(index)));
    passwordManager.removeCategory(index);
}

int Program::getCategoryToDeleteIndex() {
    int catIndex = -1;
    while (catIndex < 0) {
        displayRequest("Which category would you like to delete?");
        displayCategoriesToChoose(passwordManager.getCategories());
        std::string input = getStringDataFromUser();

        if (isNumber(input)) {
            int in = std::stoi(input);
            if (in >= 1 && in <= passwordManager.getCategories().size())
                catIndex = in - 1;
        } else displayIncorrectInput();
    }
    return catIndex;
}

void Program::sortPasswords(const std::vector<int> &sortParameters) {
    auto sortedPasswords = passwordManager.getSortedVector(sortParameters);
    displayRequest("Sorted passwords:");
    displayPasswordsWithEnter(sortedPasswords);
}

std::vector<int> Program::getSortParameters() const {
    std::vector<int> parametersToSortBy;
    bool chosen = false;
    while (!chosen) {
        displayRequest("By which parameters would you like to sort by?");
        displaySortParameters();
        std::string input = getStringDataFromUser();
        int in;
        if (isNumber(input) && (in = std::stoi(input)) >= 1 && in <= 5 &&
            std::find(parametersToSortBy.begin(), parametersToSortBy.end(), in) == parametersToSortBy.end()) {
            parametersToSortBy.push_back(in - 1);
            chosen = true;
        } else {
            in = 0;
            for (auto ch: input) {
                if (ch == ' ') {
                    if (in >= 1 && in <= 5 && std::find(parametersToSortBy.begin(), parametersToSortBy.end(), in) ==
                                              parametersToSortBy.end()) {
                        parametersToSortBy.push_back(in - 1);
                        in = 0;
                    } else {
                        displayIncorrectInput();
                    }
                } else if (isNumber(ch)) {
                    in *= 10;
                    in += ch - '0';
                } else displayIncorrectInput();
            }

            if (in >= 1 && in <= 5 &&
                std::find(parametersToSortBy.begin(), parametersToSortBy.end(), in) == parametersToSortBy.end()) {
                parametersToSortBy.push_back(in - 1);
                chosen = true;
            } else {
                displayIncorrectInput();
            }
        }
    }

    return parametersToSortBy;
}

void Program::editPassword() {
    bool chosen = false;
    int passwordIndex, parameterIdentifier;
    while (!chosen) {
        displayRequest("Which password would you like to edit? (press '0' to cancel)");
        displayPasswords(passwordManager.getPasswords());
        std::string input = getStringDataFromUser();
        if (input == "0")
            return;
        if (isNumber(input) && (passwordIndex = std::stoi(input)) >= 1 &&
            passwordIndex <= passwordManager.getPasswords().size()) {
            chosen = true;
        } else displayIncorrectInput();
    }
    passwordIndex--;

    chosen = false;
    while (!chosen) {
        displayRequest("Which parameter would you like to edit?");
        displaySortParameters();
        std::string input = getStringDataFromUser();
        if (isNumber(input) && (parameterIdentifier = std::stoi(input)) >= 1 && parameterIdentifier <= 5) {
            chosen = true;
        } else displayIncorrectInput();
    }
    parameterIdentifier--;

    std::string input;

    if (parameterIdentifier == 1) {
        input = getNewPassword();
    } else if (parameterIdentifier == 2) {
        input = getNewCategory();
    } else {
        displayRequest("Enter new value for selected parameter:");
        input = getStringDataFromUser();
    }
    std::string oldPassword = passwordManager.getPasswordAtAsString(passwordIndex);
    passwordManager.modifyPassword(passwordIndex, parameterIdentifier, input);
    fileManager.editPasswordInFile(oldPassword, passwordManager.getPasswordAtAsString(passwordIndex), passwordManager.getEncryptor());
    displaySuccess("Change applied successfully.");
}

std::string Program::getNewPassword() const {
    std::string input;
    while (true) {
        input = "no";
        do {
            if (input != "no") displayIncorrectInput();
            displayRequest("Would you like to generate password for you? (yes/no)");
            input = getStringDataFromUser();
        } while (input != "yes" && input != "no");

        if (input == "yes") {
            bool correct = true;
            do {
                if (input == "0")
                    displayError("Password size cannot be 0!");
                else if (!correct)
                    displayIncorrectInput();

                displayRequest("How long should the password be?");
                input = getStringDataFromUser();
                correct = false;
            } while (!isNumber(input) || std::stoi(input) < 0);

            int size = std::stoi(input);

            input = "no";
            do {
                if (input != "no") displayIncorrectInput();
                displayRequest("Do you want your new password to contain uppercase letters? (yes/no)");
                input = getStringDataFromUser();
            } while (input != "yes" && input != "no");

            bool uppercase;
            if (input == "yes")
                uppercase = true;

            input = "no";
            do {
                if (input != "no") displayIncorrectInput();
                displayRequest("Do you want your new password to contain special characters? (yes/no)");
                input = getStringDataFromUser();
            } while (input != "yes" && input != "no");

            bool special = false;
            if (input == "yes")
                special = true;


            std::string password;

            do {
                password = generatePassword(size, uppercase, special);
            } while (passwordManager.isPasswordAlreadyUsed(password));

            displayRequest("Your password is: " + password);

            return password;
        } else {
            displayRequest("Enter the password:");
            input = getStringDataFromUser();

            if (input.empty()) {
                displayError("Password cannot be an empty field!");
                continue;
            }

            if (doesStringContainWhitespace(input)) {
                displayError("Password cannot contain any whitespace characters!");
                continue;
            }

            std::string password = input;
            if (passwordManager.isPasswordAlreadyUsed(input)) {
                displayError("Entered password has already been used!");
                continue;
            }
            displayDefaultMessage("\033[1mGiven password:\033[0m" + passwordStrength(input) + "\033[1m.\033[0m");
            displayRequest("Would you like to keep it? (yes/no)");
            input = "no";
            do {
                if (input != "no") displayIncorrectInput();
                input = getStringDataFromUser();
            } while (input != "yes" && input != "no");

            if (input == "yes") {
                return password;
            }
        }
    }
}

std::string Program::getNewCategory() {
    std::string input;
    auto categories = passwordManager.getCategories();
    bool creatingNewCategory = false;
    while (true) {
        if (categories.empty()) {
            creatingNewCategory = true;
            displayError("There is currently no category. You have to add one right now.");
        } else {
            input = "new";
            do {
                if (input != "new") displayIncorrectInput();
                displayRequest("Would you like to use already existing category or create a new one? (existing/new)");
                input = getStringDataFromUser();
            } while (input != "existing" && input != "new");

            if (input == "new")
                creatingNewCategory = true;
        }

        if (creatingNewCategory) {
            addNewCategory();
            return passwordManager.getNewestCategory();
        } else {
            displayRequest("Choose a category for your password:");
            displayCategoriesToChoose(passwordManager.getCategories());
            input = getStringDataFromUser();
            int in;
            if (isNumber(input) && (in = std::stoi(input)) >= 1 && in <= categories.size()) {
                return passwordManager.getCategories().at(in - 1);
            } else displayIncorrectInput();
        }
    }
}
