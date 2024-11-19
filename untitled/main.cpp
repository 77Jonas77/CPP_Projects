#include <iostream>
using std::cout;
using std::endl;
int main() {
    int min=1, max=1000000;

    for(int i=0;i<20;i++){
        int half = (max+min)/2;
        cout << max << " " << min << endl;
        cout << "Czy jest to: " << half << "?" << endl;

        char input;
        std::cin >> input;

        switch(input){
            case 's':
                max=half;
                break;
            case 'b':
                min=half;
                break;
            case 'y':
                cout << "Pomyslana liczba to " << half << endl;
                i=20;
                break;
        }
    }
    return 0;
}
