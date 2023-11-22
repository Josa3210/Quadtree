//
// Created by Joeri on 11/22/2023.
//

#include <AxisAlignedBoundingBox.h>
#include <catch.hpp>

TEST_CASE("Check collisions on AABB"){
    AxisAlignedBoundingBox box1 = AxisAlignedBoundingBox({10,10},10,10);
    AxisAlignedBoundingBox box2 = AxisAlignedBoundingBox({25,25},10,10);

    REQUIRE( box1.collides(box2) == false );

    box2.setOrigin({15,15});

    REQUIRE(box1.collides(box2) == true);
}
