#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
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
        return  1. / a * Point(x, y);
    }
    Point e(){
        return operator/(norm());
    }
    Point projection(Point a){
        return operator*(a.e()) * a.e();
    }
    Point perpendicular_left(){
        return Point(-y, x);
    }
    Point perpendicular_right(){
        return Point(y, -x);
    }
};
Point operator*(double k, Point a){
    return Point(k * a.x, k * a.y);
}
auto operator==(vector<Point> ans, vector<Point> res){
    long int s;
    if (ans.size() == res.size()){
        for (auto i: ans) {
            s = count(res.begin(),res.end(), i);
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
    Segment(Point _a, Point _b){
        a = _a;
        b = _b;
    }
    Segment(double ax, double ay, double bx, double by): a(ax,ay), b(bx,by) {}
    double length(){
        return (b - a).norm();
    }
    bool operator== (Segment s){
        return a == s.a && b == s.b;
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
    virtual vector<Point> intersection(Segment s) {
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
};

class Rectangle: public Line {
public:
    Point v[4];
    double l;
    Rectangle(Segment _s, double _l){
        l = _l;
        v[0] = _s.a;
        v[1] = _s.b;
        v[2] = v[1] + _l * (v[1] - v[0]).perpendicular_left().e();
        v[3] = v[0] + _l * (v[1] - v[0]).perpendicular_left().e();
    }
    Rectangle(Point a, Point b, double _l){
        l = _l;
        v[0] = a;
        v[1] = b;
        v[2] = v[1] + _l * (v[1] - v[0]).perpendicular_left().e();
        v[3] = v[0] + _l * (v[1] - v[0]).perpendicular_left().e();
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
    virtual vector<Point> intersection(Segment q) {};
};
class Square: public Rectangle {
public:
    Square(double ax, double ay, double bx, double by):
            Rectangle(Point(ax, ay), Point(bx,by), Segment(Point(ax, ay), Point(bx,by)).length()) {}
    virtual double length() {
        return 4. * l;
    }
    virtual vector<Point> intersection(Segment q) {};
};

TEST(Point, Projection){
    ASSERT_TRUE(Point(5,5) == Point(4,6).projection(Point(7,7)));
};
TEST(Segment, Length){
    ASSERT_DOUBLE_EQ(Segment(1,3,3,3).length(),(Point(1,3) - Point(3,3)).norm());
};
TEST(Segment, Length_oy){ // ||oy = 3
    ASSERT_DOUBLE_EQ(Segment(1,1,4,1).length(),(Point(1,1) - Point(4,1)).norm());
};
TEST(Segment, Intersection_Segment){
    vector<Point> ans = { Point(4,4) };
    vector<Point> res = Segment(2,3,6,5).intersection(Segment(3,5,6,2));
    ASSERT_TRUE(ans == res);
};
TEST(Segment, Intersection_Segment_ox){ // ||ox
    vector<Point> ans = { Point(3,3) };
    vector<Point> res = Segment(1,3,5,3).intersection(Segment(2,4,5,1));
    ASSERT_TRUE(ans == res);
};
TEST(Segment, Intersection_Segment_oy){ // ||oy
    vector<Point> ans = { Point(3,3) };
    vector<Point> res = Segment(2,4,4,2).intersection(Segment(3,1,3,5));
    ASSERT_TRUE(ans == res);
};
TEST(Segment, Intersection_Segment_parallel){ // ||oy
    vector<Point> ans;
    vector<Point> res = Segment(1,3,3,5).intersection(Segment(2,1,4,3));
    ASSERT_TRUE(ans == res);
};
TEST(Segment, Intersection_Segment_noIntersection){ // ||oy
    vector<Point> ans;
    vector<Point> res = Segment(1,3,3,5).intersection(Segment(4,2,5,1));
    ASSERT_TRUE(ans == res);
};
TEST(Segment, Projection){
    ASSERT_TRUE(Segment(3,3,5,5) == Segment(2,4,4,6).projection(Point(7,7)));
};
TEST(Circle, Length){
    ASSERT_DOUBLE_EQ(Circle(Point(1,2),3).length(), 3. * 2 * M_PI );
};
TEST(Circle, Projection){
    ASSERT_TRUE(Segment(2.5,2.5,4.5,4.5) == Circle(Point(3,4),(Point(2,3) - Point(3,4)).norm()).projection(Point(5,5)));
};
TEST(Circle, Intersection_Segment_1){
    vector<Point> ans = { Point(sqrt(2),sqrt(2)) };
    ASSERT_TRUE(ans == Circle(Point(0,0),2).intersection(Segment(0,0,3,3)));
};
TEST(Circle, Intersection_Segment_2){
    vector<Point> ans = { Point(sqrt(2),sqrt(2)), Point(-sqrt(2),-sqrt(2)) };
    ASSERT_TRUE(ans == Circle(Point(0,0),2).intersection(Segment(-3,-3,3,3)));
};
TEST(Circle, Intersection_Segment_ox_1){
    vector<Point> ans = { Point(sqrt(2),sqrt(2)) };
    ASSERT_TRUE(ans == Circle(Point(4,4),2).intersection(Segment(0,sqrt(2),3,sqrt(2))));
};
TEST(Circle, Intersection_Segment_ox_2){
    vector<Point> ans = { Point(sqrt(2),sqrt(2)), Point(-sqrt(2),sqrt(2)) };
    ASSERT_TRUE(ans == Circle(Point(4,4),2).intersection(Segment(-3,sqrt(2),3,sqrt(2))));
};
TEST(Circle, Intersection_Segment_oy_1){
    vector<Point> ans = { Point(sqrt(2),sqrt(2)) };
    ASSERT_TRUE(ans == Circle(Point(4,4),2).intersection(Segment(sqrt(2),0,sqrt(2),3)));
};
TEST(Circle, Intersection_Segment_oy_2){
    vector<Point> ans = { Point(sqrt(2),sqrt(2)), Point(sqrt(2),-sqrt(2)) };
    ASSERT_TRUE(ans == Circle(Point(4,4),2).intersection(Segment(sqrt(2),-3,sqrt(2),3)));
};
TEST(Circle, Intersection_Segment_no){
    vector<Point> ans;
    ASSERT_TRUE(ans == Circle(Point(4,4),2).intersection(Segment(1,-3,2,-2)));
};
TEST(Circle, Intersection_Segment_tangent){
    vector<Point> ans;
    ASSERT_TRUE(ans == Circle(Point(4,4),2).intersection(Segment(2*sqrt(2),0,0,2*sqrt(2))));
};
TEST(Rectangle, Length){
    ASSERT_DOUBLE_EQ(Rectangle(1,1,4,1,2).length(),10);
};
TEST(Rectangle, Projection){
    ASSERT_TRUE(Segment(2,2,4.5,4.5) == Rectangle(1,3,4,3,2).projection(Point(2,2)));
};
TEST(Square, Length){
    ASSERT_DOUBLE_EQ(Square(1,1,4,1).length(),12);
};
TEST(Square, Projection){
    ASSERT_TRUE(Segment(2,2,4,4) == Square(1,3,3,3).projection(Point(2,2)));
};
int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
