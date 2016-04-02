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

int main(){
}