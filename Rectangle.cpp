//
// Created by Esteno on 13.04.2016.
//

#include "Rectangle.h"

Rectangle::Rectangle(Segment _s, double _l){
    l = _l;
    v[0] = _s.a;
    v[1] = _s.b;
    v[2] = v[1] + _l * (v[1] - v[0]).perpendicular_left().e();
    v[3] = v[0] + _l * (v[1] - v[0]).perpendicular_left().e();
}
Rectangle::Rectangle(Point a, Point b, double _l){
    l = _l;
    v[0] = a;
    v[1] = b;
    v[2] = v[1] + _l * (v[1] - v[0]).perpendicular_left().e();
    v[3] = v[0] + _l * (v[1] - v[0]).perpendicular_left().e();
}
Rectangle::Rectangle(double ax, double ay, double bx, double by, double _l){
    l = _l;
    v[0] = Point(ax,ay);
    v[1] = Point(bx,by);
    v[2] = v[1] + _l * ((v[1] - v[0]).perpendicular_left().e());
    v[3] = v[0] + _l * ((v[1] - v[0]).perpendicular_left().e());
}

double Rectangle::length(){
    return (Segment(v[0], v[1]).length() + l)*2;
}

Segment Rectangle::projection(Point m){
    double min = v[0] * m.e();
    double max = min;
    for (int i = 1; i < 3; ++i) {
        double scalar = v[i] * m.e();
        if (scalar > max){
            max = scalar;
        } else if (scalar < min){
            min = scalar;
        }
    }
    return Segment(min * m.e(), max * m.e());
}

vector<Point> Rectangle::intersection(Segment q){};

Square::Square(double ax, double ay, double bx, double by): Rectangle(Point(ax, ay), Point(bx,by), Segment(Point(ax, ay), Point(bx,by)).length()){}
