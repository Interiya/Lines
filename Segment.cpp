//
// Created by Esteno on 13.04.2016.
//

#include "Segment.h"


vector<Point> Segment::intersection(Segment m){
    double ix, jx, kx, iy, jy, ky;
    double t1, t2;
    double n1x, n1y, n2x, n2y; //координаты точки
    ix = a.x - b.x;
    jx = m.b.x - m.a.x;
    kx = m.b.x - b.x;
    iy = a.y - b.y;
    jy = m.b.y - m.a.y;
    ky = m.b.y - b.y;

    vector<Point> ret;
    double t = (jx * iy - ix * jy);
    if (t == 0) return ret;
    t2 = (kx * iy - ky * ix) / t;
    if (ix) {
        t1 = (kx - t2 * jx) / ix;
    } else {
        t1 = (ky - t2 * jy) / iy;
    }
    n1x = a.x * t1 + (1 - t1) * b.x;
    n1y = a.y * t1 + (1 - t1) * b.y;
    n2x = m.a.x * t2 + (1 - t2) * m.b.x;
    n2y = m.a.y * t2 + (1 - t2) * m.b.y;
    if ((n1x < a.x) || (n1x > b.x) ||
        (n2x < m.a.x) || (n2x > m.b.x)) return ret;
    ret.push_back(Point(n1x,n1y));
    return ret;
}

bool operator== (const Segment s, const Segment c){
    return c.a == s.a && c.b == s.b;
}
