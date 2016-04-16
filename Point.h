//
// Created by Esteno on 13.04.2016.
//

#ifndef LINES_POINT_H
#define LINES_POINT_H
#include <vector>
#include <algorithm>
#include <cmath>
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
inline Point operator*(double k, Point a){

    return Point(k * a.x, k * a.y);
}
bool operator== (const Point& a, const Point& b);

bool operator==(vector<Point> ans, vector<Point> res);

#endif //LINES_POINT_H
