//
// Created by Esteno on 13.04.2016.
//

#include "Circle.h"
Segment Circle::projection(Point m){
    return Segment((c.projection(m) * m.e() - r) * m.e(),
                   (c.projection(m) * m.e() + r) * m.e());
}

vector<Point> Circle::intersection(Segment s) {
    vector<Point> res;
    Point p = s.a - s.b;
    double a = - (p * p);
    double b = - 2 * (p * s.b );
    double c = pow(r,2) - (s.b * s.b) ;
    double d = pow(b,2) - 4 * a * c;
    if (d > 0) {
        double t1 = (-b - sqrt(d)) / (2 * a);
        double t2 = (-b + sqrt(d)) / (2 * a);
        if (t1 >= 0 && t1 <= 1) res.push_back(Point(t1 * p + s.b));
        if (t2 >= 0 && t2 <= 1) res.push_back(Point(t2 * p + s.b));
        return res;
    } else return res;
};