//
// Created by Jonasz Sójka on 15/05/2023.
//

#include "UsefulMethods.h"
#include "filesystem"

bool UsefulMethods::isNumber(const std::string& str) {
    for (char ch : str) {
        if (!std::isdigit(ch)) {
            return false;
        }
    }
    return true;
}

bool UsefulMethods::categoryExists(std::string& category, std::vector<std::string>& categoryList) {
    auto index = std::find(categoryList.begin(), categoryList.end(),category);
    return index != categoryList.end();
}

bool UsefulMethods::containsValue(const std::vector<std::filesystem::path> & vec , std::string value) {
    auto it = std::find(vec.begin(), vec.end(), value);
    return it != vec.end();
}

bool UsefulMethods::containsSeparator(const char separator, const std::string& value) {
    auto index = std::find(value.begin(),value.end(),separator);
    return index!=value.end();
}
