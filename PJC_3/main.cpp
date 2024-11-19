#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;

bool sumOfTwo(std::vector<int> v,int val);
void calc (std::vector<double>&v);

int main() {
    std::vector<int> v = {1,2,3};
    /*std::sort(v.begin(), v.end());

//zad1
    sumOfTwo(v,21);
     */
//zad2
/*std::vector<double> v{};
    for(int i=0;i<10;i++){
        int n;
        std::cin >> n;
        v.insert(v.begin(),n);
    }
    fmt::print("{}\n",v);

    calc(v);
    calc(v);
    calc(v);
    */
/*
//zad3(a)
    int counter10 = std::count_if(v.begin(),v.end(),[](int n){return n==10;});
    cout << counter10 << endl;
//zad3b
    auto countOdd = std::count_if(v.begin(),v.end(),[](int n){return n%2!=0;});
    cout << countOdd << endl;
//zad3c
    auto countPrime = std::count_if(v.begin(),v.end(),[](int n){
        if(n<2)
            return false;
        for(int i=2;i<n;i++){
            if(n%i==0)
                return false;
        }
        return true;
    });
    cout << countPrime << endl;
*/

    //zad4
    /*auto newName=std::string();
    std::cin >> newName;
    auto str = std::string();
    std::cin >> str;
   
    std::cout << str[0] << '\n';
    std::cout << "'" << str.back() << '\'' << '\n';
    std::cout << str.size() << '\n';
    std::cout << '"' << str[str.size() / 2] << "\"" << '\n';
    std::cout << '[' << str << ']' << '\n';
    std::ranges::sort(str);
    std::cout << str << '\n';
     */
    return 0;
}
bool sumOfTwo(std::vector<int> v, int val){
    int left=0;
    int right = v.size()-1;
    while(left<right){
        if(v.at(left)+v.at(right)==val){
            cout << left << " " << right << endl;
            return true;
        }else if(v.at(left)+v.at(right)>val){
            right--;
        }else{
            left++;
        }
    }
    return false;
}

bool czyParz(int n){
    return n%2==0;
}

void calc(std::vector<double>&v){
    static int count=0;
    ++count;
    if(czyParz(count)){
        v.at(0) = v.at(0)+v.at(v.size()-1);
    }else if(!czyParz(count)){
        v.at(0)=v.at(0)-v.at(v.size()-1);
    }
    v.erase(v.end()-1);
}