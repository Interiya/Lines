#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <algorithm>

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
bool operator==(vector<Point> ans, vector<Point> res){
    long int s;
    if (ans.size() == res.size()){
        for (int i = 0; i < ans.size(); ++i) {
            s = count(res.begin(),res.end(),ans[i]);
            if (s == 0) return false;
        }
        return true;
    } else return false;
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

class Circle: public Line {
    Point c;
    double r;
public:
    Circle (Point _c, double _r): c(_c), r(_r) {}
    double length (){
        return r * 2 * M_PI;
    }
    Segment projection(Point m){
        return Segment((c.projection(m) * m.e() - r) * m.e(),
                       (c.projection(m) * m.e() + r) * m.e());
    }
    virtual vector<Point> intersection(Segment q) {

    };
};

class Rectangle: public Line {
public:
    Point v[4];
    double l;
    Rectangle(Segment _s, double _l){
        l = _l;
        v[0] = _s.a;
        v[1] = _s.b;
        v[2] = v[1] + _l * ((v[1] - v[0]).perpendicular_left() /
                            (v[1] - v[0]).perpendicular_left().norm());
        v[3] = v[0] + _l * ((v[1] - v[0]).perpendicular_left() /
                            (v[1] - v[0]).perpendicular_left().norm());
    }
    Rectangle(Point a, Point b, double _l){
        l = _l;
        v[0] = a;
        v[1] = b;
        v[2] = v[1] + _l * ((v[1] - v[0]).perpendicular_left() /
                            (v[1] - v[0]).perpendicular_left().norm());
        v[3] = v[0] + _l * ((v[1] - v[0]).perpendicular_left() /
                            (v[1] - v[0]).perpendicular_left().norm());
    }
    Rectangle(double ax, double ay, double bx, double by, double _l){
        l = _l;
        v[0] = Point(ax,ay);
        v[1] = Point(bx,by);
        v[2] = v[1] + _l * ((v[1] - v[0]).perpendicular_left() /
                            (v[1] - v[0]).perpendicular_left().norm());
        v[3] = v[0] + _l * ((v[1] - v[0]).perpendicular_left() /
                            (v[1] - v[0]).perpendicular_left().norm());
    }
    double length (){
        return (Segment(v[0], v[1]).length() + l)*2;
    }
    virtual Segment projection(Point m){
        double scalar;
        double min = v[0] * m.e();
        double max = min;
        for (int i = 1; i < 3; ++i) {
            scalar = v[i] * m.e();
            if (scalar > max){
                max = scalar;
            } else if (scalar < min){
                min = scalar;
            }
        }
        return Segment(min * m.e(), max * m.e());
    }
    virtual vector<Point> intersection(Segment q) {};
};
class Square: public Rectangle {
public:
    Square(double ax, double ay, double bx, double by):
            Rectangle(Point(ax, ay), Point(bx,by), Segment(Point(ax, ay), Point(bx,by)).length()) {}
    virtual vector<Point> intersection(Segment q) {};
};
int main(){
}