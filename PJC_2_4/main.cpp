#include <iostream>
#include <vector>
#include <cmath>

using std::cout;
using std::endl;

bool isPrime(int number);

int main() {
    int input;
    std::vector<int> vec;
    while(input>=0){
        std::cin >> input;
        if(input<0){
            break;
        }else{
            vec.push_back(input);
        }
    }

    for(int i=0;i<vec.size();i++){
        if(isPrime(vec.at(i))) {
            cout << vec.at(i) << " is prime." << endl;
        }else{
            cout << vec.at(i) << " is not prime." << endl;
        }
    }
    return 0;
}

bool isPrime(int number){
    if (number < 2) return true;
    for (int i = 2; i <= sqrt(number); i++) {
        if (number % i == 0) return false;
    }
    return true;
}
