//
// Created by Esteno on 13.04.2016.
//

#ifndef LINES_LINE_H
#define LINES_LINE_H
#include "Point.h"
class Segment;
class Circle;
class Rectangle;
class Square;

class Line {
public:
    virtual double length() = 0;
    virtual Segment projection(Point m) = 0;
    virtual vector<Point> intersection(Segment q) = 0;
};

#endif //LINES_LINE_H
