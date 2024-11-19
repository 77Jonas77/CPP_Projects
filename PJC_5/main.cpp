#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using std::cout;
using std::endl;

struct Point {
    double x, y;
};

struct Rect {
    Point ld, rd;
};

std::vector<double>process(const Rect* rects, size_t sz,std::function<double(Rect)> f){
    std::vector<double> v{};
    for(size_t i = 0; i < sz; ++i){
        v.push_back(f(rects[i]));
        cout << f(rects[i]) << endl;
    }
    return v;
}
int main() {
    Point p1 ={0,4};
    Point p2 ={4,1};
    Point p3 ={-6,3};
    Point p4 ={6,-2};
    Point p5 ={-7,4};
    Point p6 ={8,-4};

    Rect arr[] = {{p1,p2},{p3,p4},{p5,p6}};
    auto process_arg = [](Rect p1)->double{return sqrt(pow(p1.ld.x-p1.rd.x,2)+pow(+p1.ld.y-p1.rd.y,2));};
    process(arr,3,process_arg);

    return 0;
}
