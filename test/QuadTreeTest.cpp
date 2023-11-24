//
// Created by Joeri on 11/23/2023.
//

#include <iostream>
#include "QuadTree.h"
#include "catch.hpp"

TEST_CASE("Test qt"){
    AxisAlignedBoundingBox object1 = AxisAlignedBoundingBox({10,10},5,5);
    AxisAlignedBoundingBox object2 = AxisAlignedBoundingBox({12,12},1,1);
    Quadtree<int> qt = Quadtree<int>(object1,2);
    qt.insert(object2,3);
    REQUIRE(qt.isSubdivided() == false);
    std::cout << qt << std::endl;
}
