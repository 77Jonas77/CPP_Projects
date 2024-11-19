//
// Created by Jonasz Sójka on 11/05/2023.
//

#include <iostream>
#include "Rect.h"
#include "cmath"

Rect::Rect() {
    Rect::x = 0;
    Rect::y = 0;
}

Rect::Rect(double s) {
    Rect::x = s;
    Rect::y = s;
}

Rect::Rect(double x, double y) {
    Rect::x = x;
    Rect::y = y;
}

double Rect::getX() {
    return Rect::x;
}

double Rect::getY() {
    return Rect::y;
}

double Rect::getDiagonal() {
    return std::sqrt(std::pow(Rect::x, 2) + std::pow(Rect::y, 2));
}

double Rect::getArea() const {
    return Rect::x * Rect::y;
}

bool Rect::isLargerThan(const Rect &p2) {
    return this->getArea() > p2.getArea();
}

void Rect::info() {
    std::cout << "RECT[" << Rect::x << "," << Rect::y << "]" << std::endl;
}