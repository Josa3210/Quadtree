//
// Created by Joeri on 11/23/2023.
//

#include "QuadTree.h"

template<typename MetadataType>
Quadtree<MetadataType>::Quadtree(const AxisAlignedBoundingBox &bounds, unsigned int region_capacity) : bounds(bounds), capacity(region_capacity){}

template<typename MetadataType>
void Quadtree<MetadataType>::insert(const AxisAlignedBoundingBox &aabb, const MetadataType &meta) {

}

template<typename MetadataType>
auto Quadtree<MetadataType>::begin() {
    return nullptr;
}

template<typename MetadataType>
auto Quadtree<MetadataType>::end() {
    return nullptr;
}