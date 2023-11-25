//
// Created by Joeri on 11/23/2023.
//

#include <iostream>
#include "QuadTree.h"
#include "catch.hpp"
#include "unordered_set_extension.h"

TEST_CASE("Test creation of QuadTree") {
    Quadtree<std::string> quadtree1 = Quadtree<std::string>();

    REQUIRE(quadtree1.getBounds().getOrigin() == Point(0, 0));
    REQUIRE(quadtree1.getBounds().getLength() == 0);
    REQUIRE(quadtree1.getBounds().getHeight() == 0);

    REQUIRE(quadtree1.isDivided() == false);
    REQUIRE(quadtree1.getRegionCapacity() == 0);

    AxisAlignedBoundingBox boxqt2 = AxisAlignedBoundingBox({10, 10}, 5, 5);
    Quadtree<int> quadtree2 = Quadtree<int>(boxqt2, 2);

    REQUIRE(quadtree2.getBounds().getOrigin() == boxqt2.getOrigin());
    REQUIRE(quadtree2.getBounds().getLength() == boxqt2.getLength());
    REQUIRE(quadtree2.getBounds().getHeight() == boxqt2.getHeight());

    REQUIRE(quadtree2.isDivided() == false);
    REQUIRE(quadtree2.getRegionCapacity() == 2);
}

TEST_CASE("Insert objects in QuadTree") {
    AxisAlignedBoundingBox boxqt = AxisAlignedBoundingBox({10, 10}, 10, 10);
    Quadtree<std::string> quadtree = Quadtree<std::string>(boxqt, 2);

    REQUIRE(quadtree.getObjects().empty());

    AxisAlignedBoundingBox testBox1 = AxisAlignedBoundingBox({25, 25}, 2, 2);
    quadtree.insert(testBox1, "TestBox1");

    REQUIRE(quadtree.getObjects().empty());

    AxisAlignedBoundingBox testBox2 = AxisAlignedBoundingBox({5, 5}, 2, 2);
    quadtree.insert(testBox2, "TestBox2");

    auto object1 = quadtree.getObjects().at(0);
    REQUIRE(std::get<0>(object1) == testBox2);
    REQUIRE(std::get<1>(object1) == "TestBox2");
}

TEST_CASE("Division of QuadTree when capacity is full") {
    AxisAlignedBoundingBox boxqt = AxisAlignedBoundingBox({100, 100}, 100, 100);
    Quadtree<std::string> quadtree = Quadtree<std::string>(boxqt, 2);

    REQUIRE(quadtree.getObjects().empty());

    // Will end up in north-west quadrant
    AxisAlignedBoundingBox testBox1 = AxisAlignedBoundingBox({55, 55}, 2, 2);
    quadtree.insert(testBox1, "TestBox1");

    // Will end up in south-east quadrant
    AxisAlignedBoundingBox testBox2 = AxisAlignedBoundingBox({120, 120}, 6, 6);
    quadtree.insert(testBox2, "TestBox2");

    REQUIRE(quadtree.getObjects().size() == 2);
    REQUIRE(quadtree.isDivided() == false);

    // Will end up in north-east quadrant
    AxisAlignedBoundingBox testBox3 = AxisAlignedBoundingBox({120, 60}, 2, 2);
    quadtree.insert(testBox3, "TestBox3");

    REQUIRE(quadtree.isDivided());
    REQUIRE(quadtree.getObjects().empty());

    REQUIRE(quadtree.getNorthEast()->isDivided() == false);
    REQUIRE(quadtree.getSouthEast()->isDivided() == false);
    REQUIRE(quadtree.getSouthWest()->isDivided() == false);
    REQUIRE(quadtree.getNorthWest()->isDivided() == false);

    REQUIRE(std::get<0>(quadtree.getNorthWest()->getObjects().at(0)) == testBox1);
    REQUIRE(std::get<0>(quadtree.getSouthEast()->getObjects().at(0)) == testBox2);
    REQUIRE(std::get<0>(quadtree.getNorthEast()->getObjects().at(0)) == testBox3);

    // Will collide with multiple quadtrees, so will end up in parent
    AxisAlignedBoundingBox testBox4 = AxisAlignedBoundingBox({101, 101}, 5, 5);
    quadtree.insert(testBox4, "TestBox4");

    REQUIRE(std::get<0>(quadtree.getObjects().at(0)) == testBox4);

    quadtree.show("");
}

TEST_CASE("Querying region in Quadtree without division") {
    AxisAlignedBoundingBox boxqt = AxisAlignedBoundingBox({100, 100}, 100, 100);
    Quadtree<std::string> quadtree = Quadtree<std::string>(boxqt, 10);


    // Will end up in north-east quadrant
    AxisAlignedBoundingBox testBox1 = AxisAlignedBoundingBox({150, 50}, 10, 10);
    quadtree.insert(testBox1, "TestBox1");

    // Will end up in south-east quadrant
    AxisAlignedBoundingBox testBox2 = AxisAlignedBoundingBox({150, 150}, 10, 10);
    quadtree.insert(testBox2, "TestBox2");

    // Will end up in the south-west quadrant
    AxisAlignedBoundingBox testBox3 = AxisAlignedBoundingBox({50, 150}, 10, 10);
    quadtree.insert(testBox3, "TestBox3");

    // Will end up in north-west quadrant
    AxisAlignedBoundingBox testBox4 = AxisAlignedBoundingBox({50, 50}, 10, 10);
    quadtree.insert(testBox4, "TestBox4");

    REQUIRE_FALSE(quadtree.isDivided());

    AxisAlignedBoundingBox toQueryRegion = AxisAlignedBoundingBox({150, 50}, 50, 50);
    auto items = quadtree.query_region(toQueryRegion);

    REQUIRE(items.size() == 1);
    REQUIRE(items.count("TestBox1") == 1);

    toQueryRegion.setOrigin({150, 150});
    items = quadtree.query_region(toQueryRegion);

    REQUIRE(items.size() == 1);
    REQUIRE(items.count("TestBox2") == 1);

    toQueryRegion.setOrigin({50, 150});
    items = quadtree.query_region(toQueryRegion);

    REQUIRE(items.size() == 1);
    REQUIRE(items.count("TestBox3") == 1);

    toQueryRegion.setOrigin({50, 50});
    items = quadtree.query_region(toQueryRegion);

    REQUIRE(items.size() == 1);
    REQUIRE(items.count("TestBox4") == 1);

    // Add another aabb in the northeast quadrant that does not touch TestBox1
    AxisAlignedBoundingBox testBox5 = AxisAlignedBoundingBox({130, 30}, 5, 5);
    quadtree.insert(testBox5, "TestBox5");

    toQueryRegion.setOrigin({150, 50});
    items = quadtree.query_region(toQueryRegion);

    REQUIRE(items.size() == 2);
    REQUIRE(items.count("TestBox1") == 1);
    REQUIRE(items.count("TestBox5") == 1);

    // Add another aabb overlapping between south-east and south-west
    AxisAlignedBoundingBox testBox6 = AxisAlignedBoundingBox({100, 130}, 5, 5);
    quadtree.insert(testBox6, "TestBox6");

    // If everything is right, both sets must contain TestBox 6
    toQueryRegion.setOrigin({150, 150});
    auto items1 = quadtree.query_region(toQueryRegion);
    toQueryRegion.setOrigin({50, 150});
    auto items2 = quadtree.query_region(toQueryRegion);

    REQUIRE(items1.size() == 2);
    REQUIRE(items1.count("TestBox2") == 1);
    REQUIRE(items1.count("TestBox6") == 1);

    REQUIRE(items2.size() == 2);
    REQUIRE(items2.count("TestBox3") == 1);
    REQUIRE(items2.count("TestBox6") == 1);
}

TEST_CASE("Querying region with split quadtree") {
    AxisAlignedBoundingBox boxqt = AxisAlignedBoundingBox({100, 100}, 100, 100);
    Quadtree<std::string> quadtree = Quadtree<std::string>(boxqt, 1);

    // Will end up in north-east quadrant
    AxisAlignedBoundingBox testBox1 = AxisAlignedBoundingBox({150, 50}, 10, 10);
    quadtree.insert(testBox1, "TestBox1");

    REQUIRE_FALSE(quadtree.isDivided());

    AxisAlignedBoundingBox toQueryRegion = AxisAlignedBoundingBox({100, 100}, 100, 100);
    auto items = quadtree.query_region(toQueryRegion);

    REQUIRE(items.size() == 1);
    REQUIRE(items.count("TestBox1"));

    // Will end up in north-east quadrant
    AxisAlignedBoundingBox testBox2 = AxisAlignedBoundingBox({150, 150}, 10, 10);
    quadtree.insert(testBox2, "TestBox2");

    items = quadtree.query_region(toQueryRegion);

    REQUIRE(quadtree.isDivided());
    REQUIRE(items.size() == 2);

    REQUIRE(items.count("TestBox1"));
    REQUIRE(items.count("TestBox2"));

    // Will end up in the object list of the parent
    AxisAlignedBoundingBox testBox3 = AxisAlignedBoundingBox({100, 150}, 10, 10);
    quadtree.insert(testBox3, "TestBox3");

    items = quadtree.query_region(toQueryRegion);

    REQUIRE(std::get<1>(quadtree.getObjects().at(0)) == "TestBox3");

    REQUIRE(quadtree.isDivided());
    REQUIRE(items.size() == 3);

    REQUIRE(items.count("TestBox1"));
    REQUIRE(items.count("TestBox2"));
    REQUIRE(items.count("TestBox3"));

}