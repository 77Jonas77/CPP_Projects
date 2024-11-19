#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
int main() {
    std::map<int, std::vector<std::string>> map_slow;
    std::set<std::string> set_slowa;
    std::string input = "";
    std::cin>>input;
    while(input!="stop"){
        set_slowa.insert(input);
        std::cin>>input;
    }
    for(auto slowo : set_slowa){
        map_slow[slowo.length()].push_back(slowo);
    }
    for(auto pair : map_slow){
        for(auto el : pair.second)
        {
            std::cout<<el<< " ";
        }
        std::cout<<std::endl;
    }
    return 0;
}