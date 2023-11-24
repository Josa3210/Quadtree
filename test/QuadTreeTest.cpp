//
// Created by Joeri on 11/24/2023.
//

#include <iostream>
#include "QuadTree.h"
#include "catch.hpp"

TEST_CASE("Creation of QuadTree"){

    AxisAlignedBoundingBox box1 = AxisAlignedBoundingBox({10,10},5,5);
    QuadTree<int> qt = QuadTree<int>(box1,2);

    std::cout << qt.getBounds() << std::endl;
}

