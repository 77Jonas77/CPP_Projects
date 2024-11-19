//
// Created by krzys on 14.05.2023.
//

#include "PasswordManager.h"

PasswordManager::PasswordManager() = default;

PasswordManager::PasswordManager(const std::vector<std::string> &passwords, const std::string &key) {
    encryptor = Encryptor(key);

    auto encryptedCategories = FileManager::readCategories();

    for (const auto &eC: encryptedCategories) {
        categories.push_back(encryptor.decipherString(eC));
    }

    std::vector<std::string> undefinedCategories;
    int incorrectLines = 0;
    for (const auto &record: passwords) {
        // Dzielimy na części do wektora
        auto deciphered = encryptor.decipherString(record);
        // Sprawdzamy, czy odczytana linia ma to, co powinna zawierać linia z hasłem
        if (FileManager::isLinePossiblePassword(deciphered)) {

            std::vector<std::string> pass;
            std::string singleData;

            for (char ch: deciphered) {
                if (ch == FileManager::SEPARATOR) {
                    pass.push_back(singleData);
                    singleData = "";
                } else {
                    singleData += ch;
                }
            }
            pass.push_back(singleData);

            Password password = Password(pass.at(0), pass.at(1), pass.at(2), pass.at(3), pass.at(4));

            bool categoryAlreadyExists = false;

            for (const std::string &cat: categories) {
                if (cat == password.getCategory()) {
                    categoryAlreadyExists = true;
                    break;
                }
            }

            // jeśli istnieje i nie została już dodana
            if (!categoryAlreadyExists && std::find(undefinedCategories.begin(), undefinedCategories.end(), password.getCategory()) == undefinedCategories.end())
                undefinedCategories.push_back(password.getCategory());

            PasswordManager::passwords.push_back(password);
        } else if (!deciphered.empty()) incorrectLines++;
    }

    if (incorrectLines != 0)
        displayError(std::to_string(incorrectLines) +
                     " lines from file could not be interpreted as possible password lines. Maybe entered key was wrong.");

    if (!undefinedCategories.empty()) {
        displayRequest("There are some categories in the file with passwords, which do not currently exist (shown below).");
        for (const auto &cat: undefinedCategories)
            std::cout << "  - " << cat << std::endl;

        std::string input = "no";
        do {
            if (input != "no") displayIncorrectInput();
            displayRequest("Would you like to add them? (yes/no)");
            input = getStringDataFromUser();
        } while (input != "no" && input != "yes");

        if (input == "yes") {
            for (const auto &cat: undefinedCategories)
                categories.push_back(cat);
        }
    }

}

const std::vector<Password> &PasswordManager::getPasswords() const {
    return passwords;
}

bool PasswordManager::doesCategoryAlreadyExist(const std::string &catName) const {
    return std::find(categories.begin(), categories.end(), catName) != categories.end();
}

void PasswordManager::addCategory(const std::string &catName) {
    categories.push_back(catName);
}

const std::vector<std::string> &PasswordManager::getCategories() const {
    return categories;
}

void PasswordManager::addPassword(const std::vector<std::string> &passData, FileManager &fileManager) {
    Password password = {
            passData.at(0),
            passData.at(1),
            passData.at(2),
            passData.at(3),
            passData.at(4),
    };
    passwords.push_back(password);
    std::string pass = password.toFileLine(FileManager::SEPARATOR);

    std::string encrypted;
    encrypted = encryptor.encryptString(pass);

    fileManager.saveNewEncryptedPasswordToFile(encrypted);
}

bool PasswordManager::isPasswordAlreadyUsed(const std::string &password) const {
    for (const auto &pass: passwords) {
        if (pass.getPassword() == password)
            return true;
    }

    return false;
}

const Encryptor &PasswordManager::getEncryptor() const {
    return encryptor;
}

std::vector<Password> PasswordManager::searchPassword(std::vector<std::string> parameters) const {
    std::vector<Password> lookedUp;

    for (const auto &password: passwords) {
        bool isMatchingPattern = true;
        for (int i = 0; i < parameters.size(); i++) {
            if (!parameters.at(i).empty()) {
                std::string passData;
                switch (i) {
                    case 0:
                        passData = password.getName();
                        break;
                    case 1:
                        passData = password.getPassword();
                        break;
                    case 2:
                        passData = password.getCategory();
                        break;
                    case 3:
                        passData = password.getWebpage();
                        break;
                    case 4:
                        passData = password.getLogin();
                        break;
                }

                if (passData != parameters.at(i))
                    isMatchingPattern = false;
            }
        }

        if (isMatchingPattern)
            lookedUp.push_back(password);
    }

    return lookedUp;
}

void PasswordManager::removePassword(int index) {
    passwords.erase(passwords.begin() + index);
}

std::set<int> PasswordManager::getPasswordsBelongingToCategory(int index) const {
    std::set<int> result;

    for (int i = 0; i < passwords.size(); i++) {
        if (passwords.at(i).getCategory() == categories.at(index))
            result.insert(i);
    }

    return result;
}

void PasswordManager::removeCategory(int index) {
    categories.erase(categories.begin() + index);
}

std::vector<Password> PasswordManager::getSortedVector(const std::vector<int> &sortParameters) const {
    std::vector<Password> sortedPasswords(passwords);

    std::sort(sortedPasswords.begin(), sortedPasswords.end(),
              [sortParameters](const Password &p1, const Password &p2) // czy p1 ma być przed p2
              {
                  auto pOneVector = p1.toVector();
                  auto pTwoVector = p2.toVector();

                  toLowercase(pOneVector);
                  toLowercase(pTwoVector);

                  for (const auto &param: sortParameters) {
                      if (pOneVector.at(param) == pTwoVector.at(param)) {
                          continue;
                      } else {
                          return pOneVector.at(param) < pTwoVector.at(param);
                      }
                  }

                  return true;
              }
    );

    return sortedPasswords;
}

std::string PasswordManager::getNewestCategory() const {
    return categories.back();
}

void
PasswordManager::modifyPassword(const int passwordIndex, const int parameterIdentifier, const std::string &newValue) {
    switch (parameterIdentifier) {
        case 0:
            passwords.at(passwordIndex).setName(newValue);
            break;
        case 1:
            passwords.at(passwordIndex).setPassword(newValue);
            break;
        case 2:
            passwords.at(passwordIndex).setCategory(newValue);
            break;
        case 3:
            passwords.at(passwordIndex).setWebpage(newValue);
            break;
        case 4:
            passwords.at(passwordIndex).setLogin(newValue);
            break;
    }
}

std::vector<std::string> PasswordManager::getPasswordVectorToFile() const {
    std::vector<std::string> passwordsAsVector;
    for (const auto& p : passwords) {
        passwordsAsVector.push_back(encryptor.encryptString(p.toFileLine(FileManager::SEPARATOR)));
    }
    return passwordsAsVector;
}

std::string PasswordManager::getPasswordAtAsString(int index) const {
    return passwords.at(index).toFileLine(FileManager::SEPARATOR);
}
