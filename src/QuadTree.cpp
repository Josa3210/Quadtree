//
// Created by Joeri on 11/23/2023.
//

#include "QuadTree.h"

template<typename MetadataType>
Quadtree<MetadataType>::Quadtree(const AxisAlignedBoundingBox &bounds, unsigned int region_capacity) : bounds(bounds),
                                                                                                       capacity(
                                                                                                               region_capacity) {}

template<typename MetadataType>
void Quadtree<MetadataType>::insert(const AxisAlignedBoundingBox &aabb, const MetadataType &meta) {
    if (!subdivided) {
        if (this->objects.length() < this->capacity) {
            this->objects.push_back({aabb, meta});
        } else {
            divide();
            redivide();
        }
    } else {
        // Create "contains" in AxisAlignedBoundingBox
    }
}

template<typename MetadataType>
void Quadtree<MetadataType>::divide() {
    Point origin = bounds.getOrigin();
    double length = bounds.getLength();
    double height = bounds.getHeight();

    AxisAlignedBoundingBox ne = AxisAlignedBoundingBox(origin + Point(length/2,-height/2), length/2, height/2);
    this->northEast = new Quadtree<MetadataType>(ne,this->capacity);
    AxisAlignedBoundingBox se = AxisAlignedBoundingBox(origin + Point(length/2,height/2), length/2, height/2);
    this->northEast = new Quadtree<MetadataType>(se,this->capacity);
    AxisAlignedBoundingBox sw = AxisAlignedBoundingBox(origin + Point(-length/2,height/2), length/2, height/2);
    this->northEast = new Quadtree<MetadataType>(sw,this->capacity);
    AxisAlignedBoundingBox nw = AxisAlignedBoundingBox(origin + Point(-length/2,-height/2), length/2, height/2);
    this->northEast = new Quadtree<MetadataType>(nw,this->capacity);

    this->subdivided = true;
}

template<typename MetadataType>
void Quadtree<MetadataType>::redivide() {

}

template<typename MetadataType>
auto Quadtree<MetadataType>::begin() {
    return nullptr;
}

template<typename MetadataType>
auto Quadtree<MetadataType>::end() {
    return nullptr;
}