//
// Created by Jonasz Sójka on 11/05/2023.
//

#ifndef CW8_2_RECT_H
#define CW8_2_RECT_H


class Rect {
    double x,y;
    public:
        Rect();
        Rect(double s);
        Rect(double x, double y);
        double getX();
        double getY();
        double getDiagonal();
        double getArea() const;
        bool isLargerThan(const Rect&);
        void info();
};


#endif //CW8_2_RECT_H
