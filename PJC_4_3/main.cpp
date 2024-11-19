#include <cmath>
#include <iostream>
#include <functional>
#include <vector>

using std::vector;
using std::function;

template<typename T, typename FunType>
vector<T> filter(const vector<T> &v, FunType p) {
    std::vector<T> res;
    for (T item: v) {
        if (p(item)) res.push_back(item);
    }
    return res;
}

template<typename T, typename FunType1, typename FunType2>
vector<T> transfilt(vector<T> &v, FunType1 t, FunType2 p) {
    vector<T> res{};
    for (int i = 0; i < v.size(); ++i) {
        v.at(i) = t(v.at(i));
        if (p(v.at(i))) {
            res.push_back(v.at(i));
        }
    }
    return res;
}

template<typename T>
void printVec(const vector<T> &v) {
    std::cout << "[ ";
    for (T el: v) {
        std::cout << el << " ";
    }
    std::cout << "]" << std::endl;
}

int main() {
    vector<double> w{1.5, -3.1, 4.0, -2.0, 6.3};
    printVec(w);
    double mn = -0.5, mx = 0.5;
    vector<double> d = transfilt(w,[](auto n){return std::sin(n);}, [=](auto n)->bool{
        if(n>=mn && n<=mx)
            return true;
        return false;
    });
    printVec(w);
    printVec(d);
}


