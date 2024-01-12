//
// Created by Joeri on 11/25/2023.
//

#ifndef QUADTREE_UNORDERED_SET_EXTENSION_H
#define QUADTREE_UNORDERED_SET_EXTENSION_H

#include "unordered_set"
#include "object.h"
#include "iostream"

template<typename T1>
std::unordered_set<object<T1>,object_hash<T1>> merge(std::unordered_set<object<T1>,object_hash<T1>> set1, std::unordered_set<object<T1>,object_hash<T1>> set2) {

    // Create an empty unordered set
    std::unordered_set<object<T1>,object_hash<T1>> set;

    // Insert all elements of set2 into set
    auto it = set2.begin();
    while (it != set2.end()) {
        set.insert(*it);
        it++;
    }

    // Insert all elements of set1 into set
    it = set1.begin();
    while (it != set1.end()) {
        set.insert(*it);
        it++;
    }

    // Return the merged set
    return set;
}

template<typename T1>
std::unordered_set<T1> merge(std::unordered_set<T1> set1, std::unordered_set<T1> set2) {

    // Create an empty unordered set
    std::unordered_set<T1> set;

    // Insert all elements of set2 into set
    auto it = set2.begin();
    while (it != set2.end()) {
        set.insert(*it);
        it++;
    }

    // Insert all elements of set1 into set
    it = set1.begin();
    while (it != set1.end()) {
        set.insert(*it);
        it++;
    }

    // Return the merged set
    return set;
}


template <typename T1>
void show(std::unordered_set<object<T1>,object_hash<T1>> &set1) {
    // Print all elements of set1
    for (auto it = set1.begin(); it != set1.end(); it++) {
        std::cout << *it << ", ";
    }
    std::cout << std::endl;
}


#endif //QUADTREE_UNORDERED_SET_EXTENSION_H
