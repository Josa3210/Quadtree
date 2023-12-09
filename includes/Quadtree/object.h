//
// Created by Joeri on 11/25/2023.
//

#ifndef QUADTREE_OBJECT_H
#define QUADTREE_OBJECT_H

#include <cmath>
#include <ostream>
#include "axisAlignedBoundingBox.h"

template<typename MetadataType>
struct object {
    object(const axisAlignedBoundingBox &box, MetadataType value) : box(box), value(value) {};

    bool operator==(const object &rhs) const { return box == rhs.box; };

    bool operator!=(const object &rhs) const { return rhs != *this; }

    friend std::ostream &operator<<(std::ostream &os, const object<MetadataType> &object) {
        os << "(box: " << object.box << " value: " << object.value << ")";
        return os;
    };

    axisAlignedBoundingBox box;
    MetadataType value;
};

template<typename MetadataType>
struct object_hash {
    size_t operator()(const object<MetadataType> &object) const {
        axisAlignedBoundingBox box = object.box;
        size_t hash = std::fmod((box.getOrigin().getX() + box.getOrigin().getY() * box.getLength()), box.getHeight());
        return hash;
    }
};
#endif //QUADTREE_OBJECT_H
