//
// Created by Esteno on 13.04.2016.
//

#include "Point.h"


bool operator==(vector<Point> ans, vector<Point> res){
    long int s;
    if (ans.size() == res.size()){
        for (auto i: ans) {
            s = count(res.begin(),res.end(), i);
            if (s == 0) return false;
        }
        return true;
    } else return false;
}
