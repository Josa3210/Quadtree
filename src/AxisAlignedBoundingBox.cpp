//
// Created by Joeri on 11/22/2023.
//

#include "AxisAlignedBoundingBox.h"
#include <utility>


AxisAlignedBoundingBox::AxisAlignedBoundingBox(Point origin, double length, double height)
        : origin(origin), length(length), height(height) {}

const Point &AxisAlignedBoundingBox::getOrigin() const {
    return origin;
}

void AxisAlignedBoundingBox::setOrigin(const Point &newOrigin) {
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
    os << "origin: " << box.origin << ", length: " << box.length << ", height: " << box.height;
    return os;
}

// Check if two rectangles collide by looking if:
// - The right side of one rectangle is left of the left side of the other one
// - The lower side of one rectangle is above the upper side of the other one
//
// Based on: https://www.geeksforgeeks.org/find-two-rectangles-overlap/
bool collides(const AxisAlignedBoundingBox &one, const AxisAlignedBoundingBox &two) {
    Point oneLU = one.getOrigin();  // The upper left point of the first rectangle
    Point oneRD = one.getOrigin() + Point(one.length, one.height);  // The lower right point of the first rectangle

    Point twoLU = two.getOrigin();  // The upper left point of the second rectangle
    Point twoRD = two.getOrigin() + Point(two.length, two.height);  // The lower right point of the second rectangle

    if (oneRD.isLeft(twoLU) or twoRD.isLeft(oneLU)) {
        return true;
    }

    if (oneRD.isHigher(twoLU) or twoRD.isHigher(oneLU)) {
        return false;
    }

    return true;
}
