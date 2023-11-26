//
// Created by Joeri on 11/25/2023.
//

#ifndef QUADTREE_OBJECT_H
#define QUADTREE_OBJECT_H

#include "axisAlignedBoundingBox.h"

template <typename MetadataType>
struct object {
    object(const axisAlignedBoundingBox &box, MetadataType value);

    const axisAlignedBoundingBox &getBox() const;

    void setBox(const axisAlignedBoundingBox &box);

    MetadataType getValue() const;

    void setValue(MetadataType value);

    bool operator==(const object &rhs) const;

    bool operator!=(const object &rhs) const;

    axisAlignedBoundingBox box;
    MetadataType value;
};



#endif //QUADTREE_OBJECT_H
