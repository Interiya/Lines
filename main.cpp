#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>

using namespace std;

const double EPS = 1e-10;

class Point;
Point operator*(double k, Point x);
class Point {
public:
    double x,y;
    Point() {}
    Point(double _x, double _y): x(_x), y(_y) {}
    Point operator+ (Point a){
        return Point(x + a.x, y + a.y);
    }
    Point operator- (Point a){
        return Point(x - a.x, y - a.y);
    }
    double norm() {
        return sqrt(x * x + y * y);
    }
    bool operator== (Point a){
        return operator-(a).norm() < EPS;
    }
    double operator* (Point a){
        return x * a.x + y * a.y;
    }
    Point operator/ (double a){
        return Point(x / a, y / a);
    }
    Point e(){
        return operator/(norm());
    }
    Point projection(Point a){
        return (*this) * a.e() * a.e();
    }
    Point perpendicular_left(){
        return Point((-1) * y, x);
    }
    Point perpendicular_right(){
        return Point(y, (-1) * x);
    }
};
Point operator*(double k, Point a){
    return Point(k * a.x, k * a.y);
}

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
class Segment: public Line {
public:
    Point a,b;
    Segment() {}
    Segment(Point _a, Point _b)
    {
        a = _a;
        b = _b;
    }
    Segment(double ax, double ay, double bx, double by): a(ax,ay), b(bx,by) {}
    double length(){
        return (b - a).norm();
    }
    bool operator== (Segment s){
        return (a == s.a) && (b == s.b);
    }

    Segment projection(Point m){
        return Segment(a.projection(m), b.projection(m));
    }

    vector<Point> intersection(Segment m){
        double ix, jx, kx, iy, jy, ky;
        double t1, t2;
        double n1x, n1y, n2x, n2y; //координаты точки
        ix = a.x - b.x;
        jx = m.b.x - m.a.x;
        kx = m.b.x - b.x;
        iy = a.y - b.y;
        jy = m.b.y - m.a.y;
        ky = m.b.y - b.y;

        double t = (jx * iy - ix * jy);
        if (t == 0) throw 0;
        t2 = (kx * iy - ky * ix) / t;
        t1 = (kx - t2 * jx) / ix;

        n1x = a.x * t1 + (1 - t1) * b.x;
        n1y = a.y * t1 + (1 - t1) * b.y;
        n2x = m.a.x * t2 + (1 - t2) * m.b.x;
        n2y = m.a.y * t2 + (1 - t2) * m.b.y;
        if ((n1x < a.x) || (n1x > b.x) ||
            (n2x < m.a.x) || (n2x > m.b.x)) throw 0;
        vector<Point> ret;
        ret.push_back(Point(n1x,n1y));
        return ret;
    }
};

int main(){
}