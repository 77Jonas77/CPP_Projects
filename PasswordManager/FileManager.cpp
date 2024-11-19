//
// Created by krzys on 14.05.2023.
//

#include "FileManager.h"

const char FileManager::SEPARATOR = ';';
const std::filesystem::path FileManager::CATEGORY_PATH = std::filesystem::path("categories.txt");
const std::filesystem::path FileManager::C_MAKE_CACHE_PATH = std::filesystem::path("CMakeCache.txt");
const int FileManager::TS1LINE = 5;
const int FileManager::TS2LINE = 10;
const int FileManager::TS3LINE = 15;

std::vector<std::filesystem::path> FileManager::getFilesFromDir(const std::filesystem::path &path) {
    std::vector<std::filesystem::path> files;
    for (const auto &file: std::filesystem::directory_iterator(path)) {
        if (file.is_regular_file() && file.path().extension() == ".txt" &&
            !std::filesystem::equivalent(file, FileManager::CATEGORY_PATH) &&
            !std::filesystem::equivalent(file, FileManager::C_MAKE_CACHE_PATH)
            )
        {
            files.push_back(file.path());
        }
    }
    return files;
}

void FileManager::setFilePath(const std::filesystem::path &path) {
    FileManager::filePath = path;
}

bool FileManager::isPathToTXT(const std::filesystem::path &path) {
    return exists(path) &&
           is_regular_file(path) &&
           path.has_extension() &&
           path.extension() == ".txt" &&
           !std::filesystem::equivalent(path, FileManager::CATEGORY_PATH) &&
           !std::filesystem::equivalent(path, FileManager::C_MAKE_CACHE_PATH);
}

void FileManager::downloadDataFromFile() {
    std::fstream fileStream;
    fileStream.open(filePath, std::ios::in);

    if (!fileStream.is_open()) {
        return;
    }

    std::string line;
    int lineNumber = 0;
    while (std::getline(fileStream, line)) {
        lineNumber++;
        if (lineNumber == TS1LINE || lineNumber == TS2LINE || lineNumber == TS3LINE) {
            line = line.substr(0, line.length() - 2);
        }
        currentFileState.push_back(line);
    }
    fileStream.close();
}

void FileManager::saveCategories(const std::vector<std::string> &categories) {
    std::fstream fstream;
    fstream.open(FileManager::CATEGORY_PATH, std::ios::trunc | std::ios::out);

    for (const auto &catName: categories)
        fstream << catName << std::endl;

    fstream.close();
}

void FileManager::saveLinesToFile(const std::vector<std::string> &lines, std::ios_base::openmode mode) const {
    std::fstream fstream;
    fstream.open(filePath, mode);

    if (!fstream.is_open()) {
        displayError("Failed to save " + std::to_string(lines.size()) + " to the file!");
        return;
    }

    for (const auto &line: lines) {
        fstream << line << std::endl;
    }

    fstream.close();
}

std::vector<std::string> FileManager::readCategories() {
    std::vector<std::string> categories;

    std::fstream fileStream;
    fileStream.open(FileManager::CATEGORY_PATH, std::ios::in);

    if (!fileStream.is_open()) {
        displayError("Failed to read categories from file. You will have to create new ones.");
        return categories;
    }

    std::string cat;
    while (std::getline(fileStream, cat)) {
        categories.push_back(cat);
    }

    return categories;
}

bool FileManager::isLinePossiblePassword(const std::string &line) {
    return countCharAppInString(line, FileManager::SEPARATOR) == 4;
}

void FileManager::deletePasswords(const std::set<int> &linesToDelete) {

    for (auto reversedIterator = linesToDelete.rbegin(); reversedIterator != linesToDelete.rend(); reversedIterator++) {
        currentFileState.erase(currentFileState.begin() + *reversedIterator);
    }

    refreshTimestamp();

    displaySuccess("Successfully deleted " + std::to_string(linesToDelete.size()) + " passwords!");
}

void FileManager::deleteCategory(const std::string &encryptedCategory) {
    std::fstream fileStreamRead;
    fileStreamRead.open(FileManager::CATEGORY_PATH, std::ios::in);

    if (!fileStreamRead.is_open()) {
        displayError("Failed to delete category.");
        return;
    }

    std::string line;
    std::vector<std::string> linesToKeep;
    while (std::getline(fileStreamRead, line)) {
        if (line != encryptedCategory)
            linesToKeep.push_back(line);
    }
    fileStreamRead.close();

    std::fstream fileStreamSave;
    fileStreamSave.open(FileManager::CATEGORY_PATH, std::ios::out);

    if (!fileStreamSave.is_open()) {
        displayError("Failed to delete category.");
        return;
    }

    for (const auto &ltk: linesToKeep) {
        fileStreamSave << ltk << std::endl;
    }

    fileStreamSave.close();

    displaySuccess("Successfully deleted category!");
}

void FileManager::saveAttemptedReadTimestamp(time_t time) {
    auto localtime = std::localtime(&time);

    char tmp[9];
    std::strftime(tmp, sizeof(tmp), "%H:%M:%S", localtime);
    std::string timeAsString(tmp);

    hourTimestamp = timeAsString.substr(0, 2);
    minuteTimestamp = timeAsString.substr(3, 2);
    secondTimestamp = timeAsString.substr(6, 2);
}

void FileManager::refreshTimestamp() {
    while (currentFileState.size() < TS3LINE)
        currentFileState.push_back("");

    // Dodawanie timestamp'ów
    currentFileState.at(TS1LINE - 1) = currentFileState.at(TS1LINE - 1) + hourTimestamp;
    currentFileState.at(TS2LINE - 1) = currentFileState.at(TS2LINE - 1) + minuteTimestamp;
    currentFileState.at(TS3LINE - 1) = currentFileState.at(TS3LINE - 1) + secondTimestamp;

    saveLinesToFile(currentFileState, std::ios::trunc | std::ios::out);

    // Usuwanie timestamp'ów
    currentFileState.at(TS1LINE - 1) = currentFileState.at(TS1LINE - 1).substr(0, currentFileState.at(TS1LINE - 1).size() - 2);
    currentFileState.at(TS2LINE - 1) = currentFileState.at(TS2LINE - 1).substr(0, currentFileState.at(TS2LINE - 1).size() - 2);
    currentFileState.at(TS3LINE - 1) = currentFileState.at(TS3LINE - 1).substr(0, currentFileState.at(TS3LINE - 1).size() - 2);
}

void FileManager::saveNewEncryptedPasswordToFile(const std::string &encryptedPassword) {
    bool added = false;

    for (int i = 0; i < currentFileState.size() && !added; i++) {
        if (currentFileState.at(i).empty()) {
            currentFileState.at(i) = encryptedPassword;
            added = true;
        }
    }

    if (!added)
        currentFileState.push_back(encryptedPassword);

    refreshTimestamp();
}

const std::vector<std::string> &FileManager::getCurrentFileState() const {
    return currentFileState;
}

void FileManager::editPasswordInFile(const std::string& oldLine, const std::string& newLine, const Encryptor& encryptor) {
    for (auto &l : currentFileState) {
        if (encryptor.decipherString(l) == oldLine) {
            l = encryptor.encryptString(newLine);
            break;
        }
    }
    refreshTimestamp();
}
