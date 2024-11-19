#include <vector>
#include <iostream>
//FILTROWANIE IMION - BRAK ROZWIAZANIA + NIE BYLO NA LEKCJI

std::vector<std::string> getNamesFrom(const std::vector<std::string>& strings)  {
    std::vector<std::string> names;
    for (const auto& str : strings) {
        if (isupper(str[0])) {
            names.push_back(str);
        }
    }
    return names;
}

auto main() -> int {
    std::vector<std::string> strings{"Ewa", "essa", "kot", "Maciec", "Polska", "email", "Skowyrski"};

    auto names = getNamesFrom(strings);

    for (const auto& name : names) {
        std::cout << name << std::endl;
    }

    return 0;
}

