#include <iostream>
#define _USE_MATH_DEFINES

#include "gtest/gtest.h"
#include "Gtest.h"


int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
