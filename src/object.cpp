//
// Created by Joeri on 11/25/2023.
//
#include "object.h"

template<typename MetadataType>
object<MetadataType>::object(const axisAlignedBoundingBox &box, MetadataType value):box(box), value(value) {}

template<typename MetadataType>
const axisAlignedBoundingBox &object<MetadataType>::getBox() const {
    return box;
}

template<typename MetadataType>
void object<MetadataType>::setBox(const axisAlignedBoundingBox &box) {
    object::box = box;
}

template<typename MetadataType>
MetadataType object<MetadataType>::getValue() const {
    return value;
}

template<typename MetadataType>
void object<MetadataType>::setValue(MetadataType value) {
    object::value = value;
}
