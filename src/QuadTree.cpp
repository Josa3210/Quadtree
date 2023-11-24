//
// Created by Joeri on 11/24/2023.
//

#include "QuadTree.h"

template<typename MetadataType>
QuadTree<MetadataType>::QuadTree(const AxisAlignedBoundingBox &bounds, unsigned int regionCapacity):bounds(bounds), region_capacity(regionCapacity) {};

template<typename MetadataType>
const AxisAlignedBoundingBox &QuadTree<MetadataType>::getBounds() const {
    return bounds;
}

template<typename MetadataType>
unsigned int QuadTree<MetadataType>::getRegionCapacity() const {
    return region_capacity;
}
