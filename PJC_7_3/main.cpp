#include <iostream>
#include <fstream>
#include <map>

int main() {
    std::fstream fileIn;
    fileIn.open("/Users/jonaszsojka/CLionProjects/PJC_7_3/cmake-build-debug/XD1/xd", std::ios::in);
    std::string word;
    std::map<std::string, int> count_digits;
    int maxcount=0;
    std::string maxdig;

    if(fileIn.is_open()){
        while(fileIn >> word){
            bool isDig=true;
            for(char c: word){
                if(!isdigit(c)){
                    isDig=false;
                    break;
                }
            }
            if(isDig){
                count_digits[word]++;
            }
        }

        for(const auto& pair : count_digits){
            if(pair.second > maxcount){
                maxcount = pair.second;
                maxdig=pair.first;
            }
        }
    }
    std::cout << maxdig << " " << maxcount << std::endl;
    return 0;
}
