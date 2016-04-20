//
// Created by Esteno on 13.04.2016.
//

#include "Segment.h"


vector<Point> Segment::intersection(Segment m){
    double ix, jx, kx, iy, jy, ky;
    double t1, t2;
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
    if (t1 >= 0 && t1 <= 1 && t2 >= 0 && t2 <= 1){
        ret.push_back(Point(t1 * a + (1 - t1) * b));
        return ret;
    } else return ret;
}

bool operator== (const Segment s, const Segment c){
    return c.a == s.a && c.b == s.b;
}
