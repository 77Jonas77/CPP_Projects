#include <iostream>

template <typename A>
size_t findMax(A arr[], size_t size){
    A max = arr[0];
    size_t maxIndex;

    for(int i=0;i<size;i++){
        if(max < arr[i]){
            max = arr[i];
            maxIndex = i;
        }
    }
    return maxIndex;
}


int main() {
    //zadanie 1
    int tabI[]{1, 2, 3, 4, 5, 6};
    double tabD[]{1., 2., 3., 4.5, 7., .6};
    std::string tabS[]{"Ala", " ", "nie", " ", "ma ", "kota"};

    std::cout << findMax(tabI, 6) << std::endl;
    std::cout << findMax(tabD, 6) << std::endl;
    std::cout << findMax(tabS, 6) << std::endl;

    return 0;
}
