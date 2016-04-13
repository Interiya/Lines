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
    double a = - (pow(p.x,2) + pow(p.y,2));
    double b = - 2 * (p.x * s.b.x + p.y * s.b.y );
    double c = pow(r,2) - (pow(s.b.x,2) + pow(s.b.y,2)) ;
    double d = pow(b,2) - 4 * a * c;
    if (d > 0) {
        double t1 = (-b - sqrt(d)) / (2 * a);
        double t2 = (-b + sqrt(d)) / (2 * a);
        Point n1 = Point(p.x * t1 + s.b.x, p.y * t1 + s.b.y);
        Point n2 = Point(p.x * t2 + s.b.x, p.y * t2 + s.b.y);
        if ((n1.x >= s.a.x && n1.x <= s.b.x) && (n1.y >= s.a.y && n1.y <= s.b.y)) res.push_back(n1);
        if ((n2.x >= s.a.x && n2.x <= s.b.x) && (n2.y >= s.a.y && n2.y <= s.b.y)) res.push_back(n2);
        return res;
    } else return res;
};