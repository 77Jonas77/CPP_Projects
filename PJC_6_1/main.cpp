#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v{123, 5342, 1235, 7654, 8678};

    auto lam = [](int l1, int l2) { return l1 - l2; };
    auto projekcja = [](int n) { return n % 10; };

    std::ranges::sort(v, lam, projekcja);
    for (auto d: v) {
        std::cout << d << std::endl;
    }
    return 0;
}
