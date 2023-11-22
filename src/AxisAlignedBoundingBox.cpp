//
// Created by Joeri on 11/22/2023.
//

#include "AxisAlignedBoundingBox.h"

#include <utility>


AxisAlignedBoundingBox::AxisAlignedBoundingBox(point origin, double length, double height)
        : origin(std::move(origin)), length(length), height(height) {}

const point &AxisAlignedBoundingBox::getOrigin() const {
    return origin;
}

void AxisAlignedBoundingBox::setOrigin(const point &newOrigin) {
    AxisAlignedBoundingBox::origin = newOrigin;
}

double AxisAlignedBoundingBox::getLength() const {
    return length;
}

void AxisAlignedBoundingBox::setLength(double newLength) {
    AxisAlignedBoundingBox::length = newLength;
}

double AxisAlignedBoundingBox::getHeight() const {
    return height;
}

void AxisAlignedBoundingBox::setHeight(double newHeight) {
    AxisAlignedBoundingBox::height = newHeight;
}

std::ostream &operator<<(std::ostream &os, const AxisAlignedBoundingBox &box) {
    os << "origin: (" << get<0>(box.origin) << ", " << get<1>(box.origin) << "), length: " << box.length << ", height: " << box.height;
    return os;
}

bool collides(const AxisAlignedBoundingBox &one, const AxisAlignedBoundingBox &two) {
    return false;
}
