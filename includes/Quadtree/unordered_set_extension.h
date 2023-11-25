//
// Created by Joeri on 11/25/2023.
//

#ifndef QUADTREE_UNORDERED_SET_EXTENSION_H
#define QUADTREE_UNORDERED_SET_EXTENSION_H

template<typename T1, typename T2>
void merge(std::unordered_set<T1, T2> set1, std::unordered_set<T1, T2> set2) {
    auto it = set2.begin();
    while (it != set2.end()) {
        set1.insert(*it);
        it++;
    }
}

template<typename T1, typename T2>
void show(std::unordered_set<T1, T2> set1) {
    for (auto it = set1.begin(); it != set1.end(); it++) {
        std::cout << *it << ", ";
    }
    std::cout << std::endl;
}

#endif //QUADTREE_UNORDERED_SET_EXTENSION_H
