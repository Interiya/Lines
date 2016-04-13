//
// Created by Esteno on 13.04.2016.
//

#ifndef LINES_CIRCLE_H
#define LINES_CIRCLE_H

#include "Line.h"
#include "Segment.h"
#include "Rectangle.h"

class Circle: public Line {
    Point c;
    double r;
public:
    Circle (Point _c, double _r): c(_c), r(_r) {}
    double length (){
        return r * 2 * M_PI;
    }
    Segment projection(Point m);
    virtual vector<Point> intersection(Segment s);
};

#endif //LINES_CIRCLE_H
