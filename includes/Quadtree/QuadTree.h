//
// Created by Joeri on 11/23/2023.
//

#ifndef QUADTREE_QUADTREE_H
#define QUADTREE_QUADTREE_H


#include <vector>
#include "AxisAlignedBoundingBox.h"

// This class is our actual quadtree
// It stores AABB’s together with some metadata
// Space Complexity: O(N)
template<typename MetadataType>
class Quadtree {
private:
    AxisAlignedBoundingBox bounds;
    unsigned int capacity;

    std::vector<std::tuple<AxisAlignedBoundingBox,MetadataType>> objects;

    bool subdivided = false;

    Quadtree<MetadataType> *northEast = nullptr;
    Quadtree<MetadataType> *southEast = nullptr;
    Quadtree<MetadataType> *southWest = nullptr;
    Quadtree<MetadataType> *northWest = nullptr;

public:
    // Constructor
    // `bounds` specifies the edges of the region that the quadtree covers.
    // `region_capacity` specifies the maximum number of objects in a single region.
    Quadtree(const AxisAlignedBoundingBox &bounds, unsigned int region_capacity);

    // This method inserts the given metadata and
    // AABB into the quadtree.
    void insert(const AxisAlignedBoundingBox &aabb, const MetadataType &meta);

// This method should return a std::unordered_set of
// all items inside the given AABB.
// The given AABB may span multiple square regions of the quadtree.
// The worst-case time-complexity of this method should be O(log(N)) for a Quadtree with N leaf nodes
// TODO: You should decide the element type of the std::unordered_set
// Your set should contain the AABB and the Metadata of all objects in the given region.
    //std::unordered_set<auto> query_region(const AxisAlignedBoundingBox& aabb) const;
// TODO: You should decide the return type for this method
// This method should return an iterator that runs over
// every element in the quadtree.
    auto begin();

// TODO: You should decide the return type for this method
// This method should return an iterator pointing
// one past the last element in the quadtree.
// When iterating from begin() to end(),
// we should visit all elements in the quadtree.
// There is no requirement with regards to
// the order that you visit these elements in.
    auto end();

    void divide();

    void redivide();
};


#endif //QUADTREE_QUADTREE_H
