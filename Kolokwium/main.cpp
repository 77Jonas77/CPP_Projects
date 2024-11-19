#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <map>
#include <array>

using std::cout;
using std::endl;


int main() {
    std::vector<int> v{4,1,3,5,6,7,8};
    cout << v.front() << endl;
    cout << v.back() << endl;
    v.pop_back();
    v.erase(v.begin() + 1,v.end()-1);
    cout << "xd " << endl;
    for(auto vec : v){
        cout << vec << endl;
    }
    srand(time(NULL));
    std::array<int,3 > x{};

    auto mapa = std::map<char,int>();
    mapa.insert('a', 2);
}

