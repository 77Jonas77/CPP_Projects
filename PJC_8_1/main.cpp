#include <iostream>
#include "Ex01Files/Point.h"

int main() {
    Point p;
    Point q(1);
    Point r(1, 2);
    p.transXY(5, 6);
    q.transX(-1).transY(-1).transXY(2, 2);
    r.setX(10).transY(-8);
    std::cout << Point::dist(p, q) << std::endl;
    std::cout << Point::dist(p, r) << std::endl;
}