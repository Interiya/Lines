//
// Created by Esteno on 13.04.2016.
//

#ifndef LINES_SEGMENT_H
#define LINES_SEGMENT_H

#include "Line.h"
#include "Circle.h"
#include "Rectangle.h"

class Segment: public Line {
public:
    Point a,b;
    Segment() {}
    Segment(Point _a, Point _b){
        a = _a;
        b = _b;
    }
    Segment(double ax, double ay, double bx, double by): a(ax,ay), b(bx,by) {}
    double length(){
        return (b - a).norm();
    }
    Segment projection(Point m){
        return Segment(a.projection(m), b.projection(m));
    }

    vector<Point> intersection(Segment m);
};


bool operator== (const Segment s, const Segment c);

#endif //LINES_SEGMENT_H
