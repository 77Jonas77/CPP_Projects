#include <cmath>
#include <iostream>
#include <functional>
#include <vector>

using std::vector;
using std::function;

template<typename T, typename FunType>
vector<T> filter(const vector<T> &v, FunType p) {
    vector<T> res;
    for(auto el: v){
        if(p(el))
            res.push_back(el);
    }
    return res;
}

template<typename T>
void printVec(const vector<T> &v) {
    std::cout << "[";
    for(auto el :v){
        std::cout << el <<", ";
    }
    std::cout << "]" << std::endl;
}

int main() {
    vector<int> v{1, -3, 4, -2, 6, -8, 5};
    printVec(v);
    vector<int> r = filter(v, [](int n) { return n % 2 == 0; });
    printVec(r);
    vector<int> s = filter(v, [](int n) { return n > 0; });

    printVec(s);

    return 0;
}
