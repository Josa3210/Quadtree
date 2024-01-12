#ifndef QUADTREE_OBJECT_H
#define QUADTREE_OBJECT_H

#include <cmath>
#include <ostream>
#include "axisAlignedBoundingBox.h"

template<typename MetadataType>
struct object {
    // Constructor for object struct
    object(const axisAlignedBoundingBox &box, MetadataType value) : box(box), value(value) {};

    // Overloaded equality operator
    bool operator==(const object &rhs) const { return box == rhs.box; };

    // Overloaded inequality operator
    bool operator!=(const object &rhs) const { return rhs != *this; }

    // Overloaded stream insertion operator
    friend std::ostream &operator<<(std::ostream &os, const object<MetadataType> &object) {
        os << "(box: " << object.box << " value: " << object.value << ")";
        return os;
    };

    // Axis-aligned bounding box
    axisAlignedBoundingBox box;

    // Metadata value
    MetadataType value;
};

template<typename MetadataType>
struct object_hash {
    // Hash function for object struct
    size_t operator()(const object<MetadataType> &object) const {
        axisAlignedBoundingBox box = object.box;
        // Calculate hash value
        auto hash = (size_t) std::fmod((box.getOrigin().getX() + box.getOrigin().getY() * box.getLength()), box.getHeight());
        return hash;
    }
};

#endif //QUADTREE_OBJECT_H
