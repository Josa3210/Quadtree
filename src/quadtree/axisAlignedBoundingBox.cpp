//
// Created by Joeri on 11/22/2023.
//

#include "axisAlignedBoundingBox.h"
#include <utility>


axisAlignedBoundingBox::axisAlignedBoundingBox(point origin, double length, double height) : origin(origin), length(length), height(height) {}

axisAlignedBoundingBox::axisAlignedBoundingBox() : origin(point(0, 0)), length(0), height(0) {};

const point &axisAlignedBoundingBox::getOrigin() const {
    return origin;
}

void axisAlignedBoundingBox::setOrigin(const point &newOrigin) {
    axisAlignedBoundingBox::origin = newOrigin;
}

double axisAlignedBoundingBox::getLength() const {
    return length;
}

void axisAlignedBoundingBox::setLength(double newLength) {
    axisAlignedBoundingBox::length = newLength;
}

double axisAlignedBoundingBox::getHeight() const {
    return height;
}

void axisAlignedBoundingBox::setHeight(double newHeight) {
    axisAlignedBoundingBox::height = newHeight;
}

std::ostream &operator<<(std::ostream &os, const axisAlignedBoundingBox &box) {
    os << "AABB(origin: " << box.origin << ", length: " << box.length << ", height: " << box.height << ")";
    return os;
}

// Check if two rectangles collide by looking if:
// - The right side of one rectangle is left of the left side of the other one
// - The lower side of one rectangle is above the upper side of the other one
//
// Based on: https://www.geeksforgeeks.org/find-two-rectangles-overlap/
bool collides(const axisAlignedBoundingBox &one, const axisAlignedBoundingBox &two) {
    point oneLU = one.getOrigin() + point(-one.length, -one.height);  // The upper left point of the first rectangle
    point oneRD = one.getOrigin() + point(one.length, one.height);  // The lower right point of the first rectangle

    point twoLU = two.getOrigin() + point(-two.length, -two.height);// The upper left point of the second rectangle
    point twoRD = two.getOrigin() + point(two.length, two.height);  // The lower right point of the second rectangle

    return !(oneRD.isLeft(twoLU) or twoRD.isLeft(oneLU) or oneLU.isLower(twoRD) or twoLU.isLower(oneRD));
}

bool axisAlignedBoundingBox::collides(const axisAlignedBoundingBox &two) {
    point oneLU = this->getOrigin() + point(-length, -height);  // The upper left point of the first rectangle
    point oneRD = this->getOrigin() + point(length, height);  // The lower right point of the first rectangle

    point twoLU = two.getOrigin() + point(-two.length, -two.height);// The upper left point of the second rectangle
    point twoRD = two.getOrigin() + point(two.length, two.height);  // The lower right point of the second rectangle

    return !(oneRD.isLeft(twoLU) or twoRD.isLeft(oneLU) or oneLU.isLower(twoRD) or twoLU.isLower(oneRD));
}

bool axisAlignedBoundingBox::contains(const axisAlignedBoundingBox &box) {
    point boxOrigin = box.getOrigin();

    return (this->contains(boxOrigin + point(box.length, box.height)) and (this->contains(boxOrigin + point(-box.length, -box.height))));
}

bool axisAlignedBoundingBox::contains(const point &point) {
    return ((point.getX() < origin.getX() + length) and (point.getX() > origin.getX() - length) and (point.getY() < origin.getY() + height) and (point.getY() > origin.getY() - height));
}

bool axisAlignedBoundingBox::operator==(const axisAlignedBoundingBox &rhs) const {
    return origin == rhs.origin && length == rhs.length && height == rhs.height;
}

bool axisAlignedBoundingBox::operator!=(const axisAlignedBoundingBox &rhs) const {
    return !(rhs == *this);
}

