//
// Created by Jonasz Sójka on 21/04/2023.
//

#include <cmath>
#include "Point.h"

Point::Point() {
    Point::x = 0;
    Point::y = 0;
}

Point::Point(double s) {
    Point::x = s;
    Point::y = s;
}

Point::Point(double x, double y) {
    Point::x = x;
    Point::y = y;
}

double Point::getX() const {
    return Point::x;
}

double Point::getY() const{
    return Point::y;
}

Point &Point::setX(double xx){
    Point::x = xx;
    return *this;
}

Point &Point::setY(double yy){
    Point::y = yy;
    return *this;
}

Point &Point::transX(double dx){
    Point::x = Point::x +dx;
    return *this;
}

Point &Point::transY(double dy){
    Point::y = Point::y +dy;
    return *this;
}

Point &Point::transXY(double dx, double dy){
    Point::y = Point::y +dy;
    Point::x = Point::x +dx;
    return *this;
}

double Point::dist(const Point &p, const Point &q){
    return std::sqrt(pow(std::abs(p.getX()-q.getX()),2) + pow(std::abs(p.getY()-q.getY()),2));
}