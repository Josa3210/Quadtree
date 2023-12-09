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

    std::unordered_set<object<T1>,object_hash<T1>> set;

    auto it = set2.begin();
    while (it != set2.end()) {
        set.insert(*it);
        it++;
    }

    it = set1.begin();
    while (it != set1.end()) {
        set.insert(*it);
        it++;
    }

    return set;
}

template<typename T1>
std::unordered_set<T1> merge(std::unordered_set<T1> set1, std::unordered_set<T1> set2) {

    std::unordered_set<T1> set;

    auto it = set2.begin();
    while (it != set2.end()) {
        set.insert(*it);
        it++;
    }

    it = set1.begin();
    while (it != set1.end()) {
        set.insert(*it);
        it++;
    }

    return set;
}


template <typename T1>
void show(std::unordered_set<object<T1>,object_hash<T1>> &set1) {
    for (auto it = set1.begin(); it != set1.end(); it++) {
        std::cout << *it << ", ";
    }
    std::cout << std::endl;
}


#endif //QUADTREE_UNORDERED_SET_EXTENSION_H
