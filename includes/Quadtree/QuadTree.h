//
// Created by Joeri on 11/24/2023.
//

#ifndef QUADTREE_QUADTREE_H
#define QUADTREE_QUADTREE_H

#include "AxisAlignedBoundingBox.h"

template <typename MetadataType>
class QuadTree {
public:
    QuadTree(const AxisAlignedBoundingBox &bounds, unsigned int regionCapacity);

    const AxisAlignedBoundingBox &getBounds() const;

    unsigned int getRegionCapacity() const;

private:
    AxisAlignedBoundingBox bounds;
    unsigned int region_capacity;
public:

};


#endif //QUADTREE_QUADTREE_H
