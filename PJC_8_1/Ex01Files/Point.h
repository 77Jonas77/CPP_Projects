//
// Created by Jonasz Sójka on 21/04/2023.
//

#ifndef PJC_8_1_POINT_H
#define PJC_8_1_POINT_H
class Point {
    double x, y;
public:
    Point();

    Point(double s);

    Point(double x, double y);

    double getX() const;

    double getY() const;

    Point &setX(double xx);

    Point &setY(double yy);

    Point &transX(double dx);

    Point &transY(double dy);

    Point &transXY(double dx, double dy);

    static double dist(const Point &p, const Point &q);
};
#endif //PJC_8_1_POINT_H
