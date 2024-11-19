#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;

bool sumOfTwo(std::vector<int> v,int val);

int main() {
    std::vector<int> v { 2, 4, 5, 8, 9, 11, 13, 15};
    std::ranges::sort(v);

//zad1
    sumOfTwo(v,21);
//zad3a
    int counter10 = std::ranges::count_if(v,[](int n){return n==10;});
    cout << counter10 << endl;
//zad3b
    auto countOdd = std::ranges::count_if(v,[](int n){return n%2!=0;});
    cout << countOdd << endl;
//zad3c
    auto countPrime = std::ranges::count_if(v,[](int n){
        if(n<2)
            return false;
        for(int i=0;i<n;i++){
            if(n%i==0)
                return false;
        }
        return true;
    });

    return 0;
}
bool sumOfTwo(std::vector<int> v,int val){
    int left = 0;
    int right = v.size()-1;
    while(left<right){
        int sum = 0;
        sum = v.at(left) + v.at(right);
        if(sum==val){
            cout << left << " " << right << endl;
            return true;
        }else if(sum>val){
            left++;
        }else{
            right--;
        }
    }
    return false;
}
