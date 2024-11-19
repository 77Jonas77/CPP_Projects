//
// Created by Jonasz Sójka on 14/05/2023.
//

#include "FileManager.h"
#include <iostream>
#include <sstream>
#include "CryptingManager.h"
#include "Password.h"
#include "vector"
#include "UsefulMethods.h"
#include <ctime>

FileManager::FileManager(const std::filesystem::path &filePath) {
    this->setFilePath(filePath);
    this->dataFile.open(this->getFilePath(), std::ios::in);
    if (!this->dataFile.is_open()) {}
    this->dataFile.close();
}

void FileManager::saveLineToFile(const std::string &line, std::string key) {
    if (UsefulMethods::containsSeparator(FileManager::separator, CryptingManager::decryptData(line, key))) {
        this->dataFile.open(this->getFilePath(), std::ios::app);
    } else {
        this->dataFile.open(this->getCategoriesFilePath(),
                            std::ios::app);
    }
    this->dataFile << line << std::endl;
    this->dataFile.close();
}

std::vector<std::string> FileManager::loadCategories(const std::filesystem::path &categoriesFile, std::string key) {
    std::string line;
    std::vector<std::string> categoryList{};

    if (file_size(categoriesFile) != 0) {
        this->dataFile.open(categoriesFile);
        while (std::getline(this->dataFile, line)) {
            if (!UsefulMethods::containsSeparator(separator, CryptingManager::decryptData(line, key)))
                categoryList.push_back(CryptingManager::decryptData(line, key));
        }
        this->dataFile.close();
    }

    return categoryList;
}

std::vector<Password> FileManager::loadPasswords(const std::filesystem::path &passwordsFile, std::string key) {
    std::string line;
    std::vector<Password> passwList{};
    int linecounter = 0;
    int countlines = 0;

    this->dataFile.open(this->getFilePath(), std::ios::in);
    std::string lineNew;
    while (std::getline(this->dataFile, lineNew)) {
        lineNew=CryptingManager::decryptData(lineNew,key);
        if(std::count(lineNew.begin(), lineNew.end(), ';')==4)
            countlines++;
    }
    this->dataFile.close();

    this->dataFile.open(passwordsFile);
    if (countlines >= 5) {
        while (std::getline(this->dataFile, line)) {
            std::string tmp;
            line = CryptingManager::decryptData(line, key);
            std::istringstream iss(line);
            std::string token;
            int countRound = 0;
            std::string name, pass, cat,www,login;
            while (std::getline(iss, token, separator)) {
                if (countRound == 0) {
                    if (linecounter == 0 || linecounter == 4) {
                        for (int i = 0; i < token.length(); i++) {
                            if (i > 1)
                                name += token[i];
                        }
                    } else {
                        name = token;
                    }
                } else if (countRound == 1)
                    pass = token;
                else if(countRound == 2){
                    cat = token;
                }else if (countRound == 3) {
                    www=token;
                }else if(countRound == 4){
                    if (linecounter == 2) {
                        for (int i = 0; i < token.length(); i++) {
                            if (i < token.length() - 2)
                                login += token[i];
                        }
                    } else {
                        login = token;
                    }
                }
                countRound++;
            }
            passwList.push_back(Password(name, pass, cat,www,login));
            linecounter++;
        }

    } else {
        while (std::getline(this->dataFile, line)) {
            std::string tmp;
            line = CryptingManager::decryptData(line, key);
            if (std::count(line.begin(), line.end(), ';') == 4) {
                std::istringstream iss(line);
                std::string token;
                int countRound = 0;
                std::string name, pass, cat,www,login;
                while (std::getline(iss, token, separator)) {
                    if (countRound == 0) {
                        if (linecounter == 0 || linecounter == 4) {
                            if (countlines >= 1) {
                                for (int i = 0; i < token.length(); i++) {
                                    if (i > 1)
                                        name += token[i];
                                }
                            } else {
                                name = "";
                            }
                        } else {
                            name = token;
                        }
                    } else if (countRound == 1)
                        pass = token;
                    else if(countRound == 2){
                        cat=token;
                    }else if(countRound == 3){
                        www=token;
                    }else if(countRound == 4){
                        if (linecounter == 2) {
                            if (countlines >= 3) {
                                for (int i = 0; i < token.length(); i++) {
                                    if (i < token.length() - 2)
                                        login += token[i];
                                }
                            } else {
                                login = "";
                            }
                        } else {
                            login = token;
                        }
                    }
                    countRound++;
                }
                if (countlines != 0 && linecounter <= countlines)
                    passwList.push_back(Password(name, pass, cat, www,login));
                linecounter++;
            }
        }
    }
    dataFile.close();
    this->overwriteFileWithPasswords(passwList, key);

    return passwList;
}

void FileManager::overwriteFileWithPasswords(const std::vector<Password> &passwords, std::string key) {
    int linecounter = 0;
    std::string hour, minute, sec;
    this->refreshTimestamp();

    this->dataFile.open(this->getFilePath(), std::ios::out | std::ios::trunc);

    for (int i = 0; i < this->timestamp.length(); i++) {
        if (i < 2)
            hour += timestamp[i];
        else if (i >= 2 && i <= 3)
            minute += timestamp[i];
        else
            sec += timestamp[i];
    }

    if (passwords.size() < 5) {
        for (int i = 0; i < 5; i++) {
            if (i == 0) {
                if (!passwords.empty()) {
                    this->dataFile << (hour + CryptingManager::encryptData(passwords[i].getName() + separator +
                                                                           passwords[i].getPassw() + separator +
                                                                           passwords[i].getCat() +separator +passwords[i].getWww()+separator+passwords[i].getLogin(), key)) << std::endl;
                } else {
                    this->dataFile << hour << std::endl;
                }
            } else if (i == 2) {
                if (passwords.size() > i) {
                    this->dataFile << (CryptingManager::encryptData(passwords[i].getName() + separator +
                                                                    passwords[i].getPassw() + separator +
                                                                    passwords[i].getCat()+ separator + passwords[i].getWww() + separator +passwords[i].getLogin(), key) + minute) << std::endl;
                } else {
                    this->dataFile << minute << std::endl;
                }
            } else if (i == 4) {
                if (passwords.size() > i) {
                    this->dataFile << (CryptingManager::encryptData(passwords[i].getName() + separator +
                                                                    passwords[i].getPassw() + separator +
                                                                    passwords[i].getCat()+separator+passwords[i].getWww() + separator + passwords[i].getLogin(), key) + minute) << std::endl;
                } else {
                    this->dataFile << sec << std::endl;
                }
            } else {
                if (i < passwords.size()) {
                    this->dataFile << CryptingManager::encryptData(passwords[i].getName() + separator +
                                                                   passwords[i].getPassw() + separator +
                                                                   passwords[i].getCat()+separator + passwords[i].getWww()+separator + passwords[i].getLogin(), key) << std::endl;
                } else {
                    this->dataFile << "" << std::endl;
                }
            }
        }
    } else {
        for (const auto &password: passwords) {
            if (linecounter == 0) {
                this->dataFile << (hour + CryptingManager::encryptData(password.getName() + separator +
                                                                       password.getPassw() + separator +
                                                                       password.getCat() +separator+password.getWww()+separator + password.getLogin(), key)) << std::endl;
            } else if (linecounter == 2) {
                this->dataFile << (CryptingManager::encryptData(password.getName() + separator +
                                                                password.getPassw() + separator +
                                                                password.getCat()+separator+password.getWww()+separator + password.getLogin(), key) + minute) << std::endl;
            } else if (linecounter == 4) {
                this->dataFile << (sec + CryptingManager::encryptData(password.getName() + separator +
                                                                      password.getPassw() + separator +
                                                                      password.getCat()+separator+password.getWww()+separator + password.getLogin(), key)) << std::endl;
            } else {
                this->dataFile << CryptingManager::encryptData(password.getName() + separator +
                                                               password.getPassw() + separator +
                                                               password.getCat()+separator+password.getWww()+separator+password.getLogin(), key) << std::endl;
            }
            linecounter++;
        }
    }
    this->dataFile.close();
}

void FileManager::overwriteFileWithCategories(const std::vector<std::string> &categoryList, std::string key) {
    this->dataFile.open(this->getCategoriesFilePath(), std::ios::out | std::ios::trunc);

    for (const auto &cat: categoryList) {
        this->dataFile << CryptingManager::encryptData(cat, key) << std::endl;
    }
    this->dataFile.close();
}

std::vector<std::filesystem::path> FileManager::getFilesFromDirectory(const std::filesystem::path &path, std::string key) {
    std::vector<std::filesystem::path> files;

    if (std::filesystem::is_directory(path)) {
        for (const auto &entry: std::filesystem::recursive_directory_iterator(path)) {
            if (isFileTxt(entry, key) && isFileValid(entry, key)) {
                files.push_back(entry.path().filename());
            }
        }
    }
    return files;
}

bool FileManager::isFileTxt(const std::filesystem::path &path, std::string key) {
    return std::filesystem::exists(path) && std::filesystem::is_regular_file(path) && path.has_extension() &&
           path.extension() == ".txt" && isFileValid(path,key);
}

bool FileManager::isFileValid(const std::filesystem::path &path, std::string key) {
    std::fstream file;
    file.open(path, std::ios::in);

    if(path.filename()=="clion-Debug-log.txt"){
        return false;
    }
    if(path.filename()=="TargetDirectories.txt"){
        return false;
    }
    if(path.filename()=="clion-environment.txt"){
        return false;
    }
    if(path.filename()=="CMakeCache.txt"){
        return false;
    }

    if ( path.filename() == "categories.txt") {
        return false;
    }

    std::string line;
    int linecount = 0;
    int x=0;
    while (std::getline(file, line)) {
        line = CryptingManager::decryptData(line, key);
        std::string newLine;
        if (linecount == 0) {
            for (int i = 0; i < line.size(); ++i) {
                if (i > 1)
                    newLine[i - 2] = line[i];
            }
        }else if (linecount == 2) {
            for (int i = 0; i < line.size(); ++i) {
                if (i < line.size() - 2)
                    newLine[i] = line[i];
            }
        }else if (linecount == 4) {
            for (int i = 0; i < line.size(); ++i) {
                if (i > 1)
                    newLine[i - 2] = line[i];
            }
        }else {
            newLine = line;
        }
        linecount++;
        if (std::count(newLine.begin(), newLine.end(), ';') > 4 || std::count(newLine.begin(), newLine.end(), ';') == 1) {
            file.close();
            return false;
        }
    }
    file.close();
    return true;
}


const std::filesystem::path &FileManager::getFilePath() const {
    return filePath;
}

void FileManager::setFilePath(const std::filesystem::path &filePath) {
    FileManager::filePath = filePath;
}


const std::filesystem::path &FileManager::getCategoriesFilePath() const {
    return categoriesFilePath;
}

void FileManager::setCategoriesFilePath(const std::filesystem::path &categoriesFileP) {
    FileManager::categoriesFilePath = categoriesFileP;
}

const std::string &FileManager::getTimestamp() const {
    return timestamp;
}

void FileManager::setTimestamp(const std::string &timestamp) {
    FileManager::timestamp = timestamp;
}

void FileManager::refreshTimestamp() {
    std::time_t t = std::time(nullptr);
    std::tm *now = std::localtime(&t);

    std::string hour = (now->tm_hour < 10) ? "0" + std::to_string(now->tm_hour) : std::to_string(now->tm_hour);
    std::string minute = (now->tm_min < 10) ? "0" + std::to_string(now->tm_min) : std::to_string(now->tm_min);
    std::string sec = (now->tm_sec < 10) ? "0" + std::to_string(now->tm_sec) : std::to_string(now->tm_sec);

    this->setTimestamp(hour + minute + sec);
}


