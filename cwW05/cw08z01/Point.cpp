//
// Created by Jonasz Sójka on 11/05/2023.
//

#include "Point.h"
#include "cmath"

Point::Point() {
    x=0;
    y=0;
}

Point::Point(double s){
    x = s;
    y = s;
}

Point::Point(double x, double y){
    Point::x=x;
    Point::x=y;
}
//w tej metodzie nie bedziemy edytowac obiektu na rzecz ktorego jest to wywolywane

double Point::getX() const {
    return x;
}
double Point::getY() const {
    return x;
}

Point &Point::setX(double xx) {
    Point::x=xx;
    return *this;
}

Point &Point::setY(double yy) {
    Point::y=yy;
    return *this;
}

Point & Point::transX(double dx) {
    Point::x += dx;
    return * this;
}

Point & Point::transY(double dx) {
    Point::x += dx;
    return * this;
}

Point & Point::transXY(double dx, double dy) {
    Point::x += dx;
    Point::y += dy;
    return *this;
}

double Point::dist(const Point &p, const Point &q) {
    return std::sqrt(pow(std::abs(p.getX()-q.getX()),2) + pow(std::abs(p.getY()-q.getY()),2));
}