//
// Created by Esteno on 13.04.2016.
//

#ifndef LINES_RECTANGLE_H
#define LINES_RECTANGLE_H

#include "Line.h"
#include "Segment.h"
#include "Circle.h"

class Rectangle: public Line {
public:
    Point v[4];
    double l;
    Rectangle(Segment _s, double _l);
    Rectangle(Point a, Point b, double _l);
    Rectangle(double ax, double ay, double bx, double by, double _l);
    double length ();
    Segment projection(Point m);
    vector<Point> intersection(Segment q);
};

class Square: public Rectangle {
public:
    Square(double ax, double ay, double bx, double by);
    virtual double length() {
        return 4. * l;
    }
};


#endif //LINES_RECTANGLE_H
