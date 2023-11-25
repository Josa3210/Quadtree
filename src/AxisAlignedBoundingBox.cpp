//
// Created by Joeri on 11/22/2023.
//

#include "AxisAlignedBoundingBox.h"
#include <utility>


AxisAlignedBoundingBox::AxisAlignedBoundingBox(Point origin, double length, double height) : origin(origin), length(length), height(height) {}

AxisAlignedBoundingBox::AxisAlignedBoundingBox() : origin(Point(0, 0)), length(0), height(0) {};

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
    os << "AABB(origin: " << box.origin << ", length: " << box.length << ", height: " << box.height << ")";
    return os;
}

// Check if two rectangles collide by looking if:
// - The right side of one rectangle is left of the left side of the other one
// - The lower side of one rectangle is above the upper side of the other one
//
// Based on: https://www.geeksforgeeks.org/find-two-rectangles-overlap/
bool collides(const AxisAlignedBoundingBox &one, const AxisAlignedBoundingBox &two) {
    Point oneLU = one.getOrigin() + Point(-one.length, -one.height);  // The upper left point of the first rectangle
    Point oneRD = one.getOrigin() + Point(one.length, one.height);  // The lower right point of the first rectangle

    Point twoLU = two.getOrigin() + Point(-two.length, -two.height);// The upper left point of the second rectangle
    Point twoRD = two.getOrigin() + Point(two.length, two.height);  // The lower right point of the second rectangle

    return !(oneRD.isLeft(twoLU) or twoRD.isLeft(oneLU) or oneLU.isLower(twoRD) or twoLU.isLower(oneRD));
}

bool AxisAlignedBoundingBox::collides(const AxisAlignedBoundingBox &two) {
    Point oneLU = this->getOrigin() + Point(-length, -height);  // The upper left point of the first rectangle
    Point oneRD = this->getOrigin() + Point(length, height);  // The lower right point of the first rectangle

    Point twoLU = two.getOrigin() + Point(-two.length, -two.height);// The upper left point of the second rectangle
    Point twoRD = two.getOrigin() + Point(two.length, two.height);  // The lower right point of the second rectangle

    return !(oneRD.isLeft(twoLU) or twoRD.isLeft(oneLU) or oneLU.isLower(twoRD) or twoLU.isLower(oneRD));
}

bool AxisAlignedBoundingBox::contains(const AxisAlignedBoundingBox &box) {
    Point boxOrigin = box.getOrigin();

    return (this->contains(boxOrigin + Point(box.length, box.height)) and (this->contains(boxOrigin + Point(-box.length, -box.height))));
}

bool AxisAlignedBoundingBox::contains(const Point &point) {
    return ((point.getX() < origin.getX() + length) and (point.getX() > origin.getX() - length) and (point.getY() < origin.getY() + height) and (point.getY() > origin.getY() - height));
}

bool AxisAlignedBoundingBox::operator==(const AxisAlignedBoundingBox &rhs) const {
    return origin == rhs.origin && length == rhs.length && height == rhs.height;
}

bool AxisAlignedBoundingBox::operator!=(const AxisAlignedBoundingBox &rhs) const {
    return !(rhs == *this);
}

