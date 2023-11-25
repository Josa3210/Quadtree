//
// Created by Joeri on 11/22/2023.
//

#include <AxisAlignedBoundingBox.h>
#include <catch.hpp>

TEST_CASE("Check collisions on AABB"){
    AxisAlignedBoundingBox box1 = AxisAlignedBoundingBox({10,10},5,5);
    AxisAlignedBoundingBox box2 = AxisAlignedBoundingBox({25,25},5,5);

    REQUIRE( box1.collides(box2) == false );

    box2.setOrigin({20,20});

    REQUIRE(box1.collides(box2) == true);
}

TEST_CASE("Check if box contains point"){
    AxisAlignedBoundingBox containerBox = AxisAlignedBoundingBox({20,20},10,10);

    Point testPoint = Point(0,0);
    REQUIRE(containerBox.contains(testPoint) == false);

    testPoint = Point(25,25);
    REQUIRE(containerBox.contains(testPoint) == true);
}

TEST_CASE("Check if box contains box"){
    AxisAlignedBoundingBox containerBox = AxisAlignedBoundingBox({20,20},10,10);

    AxisAlignedBoundingBox containedBox = AxisAlignedBoundingBox({10,10}, 7,7);
    REQUIRE(containerBox.contains(containedBox) == false);

    containedBox.setOrigin({20,20});
    REQUIRE(containerBox.contains(containedBox) == true);
}
