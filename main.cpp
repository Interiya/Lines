#include <iostream>
#define _USE_MATH_DEFINES

#include "gtest/gtest.h"
#include "Segment.h"
#include "Circle.h"
#include "Rectangle.h"

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
TEST(Segment, Intersection_Segment_parallel){
    vector<Point> ans;
    vector<Point> res = Segment(1,3,3,5).intersection(Segment(2,1,4,3));
    ASSERT_TRUE(ans == res);
};
TEST(Segment, Intersection_Segment_noIntersection){
    vector<Point> ans;
    //vector<Point> res = Segment(1,3,3,5).intersection(Segment(4,2,5,1));
    vector<Point> res = Segment(4,2,5,1).intersection(Segment(1,3,3,5));

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
    ASSERT_TRUE(ans == Circle(Point(4,4),2).intersection(Segment(sqrt(2),0,sqrt(2.),3)));
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
