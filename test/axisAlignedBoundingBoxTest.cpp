//
// Created by Joeri on 11/22/2023.
//

#include <axisAlignedBoundingBox.h>
#include <catch.hpp>

TEST_CASE("Check collisions on AABB"){
    axisAlignedBoundingBox box1 = axisAlignedBoundingBox({10, 10}, 5, 5);
    axisAlignedBoundingBox box2 = axisAlignedBoundingBox({25, 25}, 5, 5);

    REQUIRE( box1.collides(box2) == false );

    box2.setOrigin({20,20});

    REQUIRE(box1.collides(box2) == true);
}

TEST_CASE("Check if box contains point"){
    axisAlignedBoundingBox containerBox = axisAlignedBoundingBox({20, 20}, 10, 10);

    point testPoint = point(0, 0);
    REQUIRE(containerBox.contains(testPoint) == false);

    testPoint = point(25, 25);
    REQUIRE(containerBox.contains(testPoint) == true);
}

TEST_CASE("Check if box contains box"){
    axisAlignedBoundingBox containerBox = axisAlignedBoundingBox({20, 20}, 10, 10);

    axisAlignedBoundingBox containedBox = axisAlignedBoundingBox({10, 10}, 7, 7);
    REQUIRE(containerBox.contains(containedBox) == false);

    containedBox.setOrigin({20,20});
    REQUIRE(containerBox.contains(containedBox) == true);
}
