#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <algorithm>
#define GETMAX
#define bok 16
using std::cout;
using std::endl;

double polePowierzchniGraniastoslupaPieciokatnego(double wysokosc);
double poleKwadratu();

int main() {
//#if defined(d)
// std::cout << "Hello, World!" << std::endl;
//#else
//#error erro
// std::cout << "siema" << std::endl;
//#endif
// cout << __LINE__ << endl;
// std::vector<int> vec;
// auto a = 5;
// return 0;

//zadanie 1
/*cout << __LINE__ << " " << __FILE__ << endl;
cout << __LINE__ << " " << __DATE__ << endl;*/

//zadanie 2
/*
srand(time(NULL));
std::vector<int> v;
for (int i = 0; i < 5; i++) {
v.push_back(std::rand() % 10 + 1);
cout << v.at(i);
}
cout << endl;
#ifdef GETMAX
int max = v.at(0);
for (int i = 0; i < v.size(); i++) {
if (v.at(i) > max)
max = v.at(i);
}
cout << "max: " << max << endl;
#endif
#ifdef GETMIN
int min = v.at(0);
for (int i = 0; i < v.size(); i++) {
if (v.at(i) < min)
min = v.at(i);
}
cout << "min: " << min << endl;
#endif
#if !defined(GETMIN) && !defined(GETMAX)
#error Zadna nie zostala zadeklarowana
#endif
*/

//zadanie3
//cout << poleKwadratu() << endl;
//cout << polePowierzchniGraniastoslupaPieciokatnego(2) << endl;
}

double poleKwadratu(){
    return bok*bok;
}

double polePowierzchniGraniastoslupaPieciokatnego(double wysokosc){
    return (sqrt(5)+1+(wysokosc*5))*bok;
}

