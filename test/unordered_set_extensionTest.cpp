//
// Created by Joeri on 11/25/2023.
//

#include <iostream>
#include "catch.hpp"
#include "unordered_set_extension.h"

TEST_CASE("Merging"){
    std::unordered_set<int> set1;
    set1.insert(1);
    set1.insert(2);

    std::unordered_set<int> set2;
    set2.insert(3);
    set2.insert(4);

    std::unordered_set<int> set3;
    set3 = merge(set1, set2);

    REQUIRE(set3.count(1));
    REQUIRE(set3.count(2));
    REQUIRE(set3.count(3));
    REQUIRE(set3.count(4));


}