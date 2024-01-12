//
// This class represents an AxisAlignedBoundingBox.
// An AxisAlignedBoundingBox is defined by an origin point, length, and height.
// Created by Joeri on 11/22/2023.
//

#include "axisAlignedBoundingBox.h"


// Constructor for the AxisAlignedBoundingBox class that initializes the origin, length, and height of the bounding box.
axisAlignedBoundingBox::axisAlignedBoundingBox(point origin, float length, float height) : origin(origin), length(length), height(height) {}

// Default constructor for the AxisAlignedBoundingBox class that initializes the origin, length, and height to zero.
axisAlignedBoundingBox::axisAlignedBoundingBox() : origin(point(0, 0)), length(0), height(0) {};

// Constructor for the AxisAlignedBoundingBox class that initializes the origin, length, and height of the bounding box using individual components.
axisAlignedBoundingBox::axisAlignedBoundingBox(float originX, float originY, float length, float height) : origin(point(originX, originY)), height(height), length(length) {}

// Returns the origin point of the bounding box.
const point &axisAlignedBoundingBox::getOrigin() const {
    return origin;
}

// Sets the origin point of the bounding box to a new value.
void axisAlignedBoundingBox::setOrigin(const point &newOrigin) {
    axisAlignedBoundingBox::origin = newOrigin;
}

// Returns the length of the bounding box.
float axisAlignedBoundingBox::getLength() const {
    return length;
}

// Sets the length of the bounding box to a new value.
void axisAlignedBoundingBox::setLength(float newLength) {
    axisAlignedBoundingBox::length = newLength;
}

// Returns the height of the bounding box.
float axisAlignedBoundingBox::getHeight() const {
    return height;
}

// Sets the height of the bounding box to a new value.
void axisAlignedBoundingBox::setHeight(float newHeight) {
    axisAlignedBoundingBox::height = newHeight;
}

// Overloaded insertion operator to allow printing of the axisAlignedBoundingBox object.
std::ostream &operator<<(std::ostream &os, const axisAlignedBoundingBox &box) {
    os << "AABB(origin: " << box.origin << ", length: " << box.length << ", height: " << box.height << ")";
    return os;
}

// Function to check if two axisAlignedBoundingBox objects collide.
// Uses the upper left and lower right points of each bounding box to determine collision.
// The function uses the 'isLeft' and 'isLower' functions from the 'point' class.
bool collides(const axisAlignedBoundingBox &one, const axisAlignedBoundingBox &two) {
    point oneLU = one.getOrigin();  // The upper left point of the first rectangle
    point oneRD = one.getOrigin() + point(one.length, one.height);  // The lower right point of the first rectangle
    point twoLU = two.getOrigin();// The upper left point of the second rectangle
    point twoRD = two.getOrigin() + point(two.length, two.height);  // The lower right point of the second rectangle

    // It checks if the right side of one box is left of the left side of the other box,
    // and if the lower side of one box is above the upper side of the other box.
    return !(oneRD.isLeft(twoLU) or twoRD.isLeft(oneLU) or oneLU.isLower(twoRD) or twoLU.isLower(oneRD));
}

// Checks if the current axisAlignedBoundingBox object collides with another axisAlignedBoundingBox object.
// It follows the same collision logic as the 'collides' function above, but uses this object's properties.
bool axisAlignedBoundingBox::collides(const axisAlignedBoundingBox &two) const {
    point oneLU = this->getOrigin();  // The upper left point of the first rectangle
    point oneRD = this->getOrigin() + point(length, height);  // The lower right point of the first rectangle
    point twoLU = two.getOrigin();// The upper left point of the second rectangle
    point twoRD = two.getOrigin() + point(two.length, two.height);  // The lower right point of the second rectangle

    return !(oneRD.isLeft(twoLU) or twoRD.isLeft(oneLU) or oneLU.isLower(twoRD) or twoLU.isLower(oneRD));
}

// Checks if the current axisAlignedBoundingBox object completely contains another axisAlignedBoundingBox object.
bool axisAlignedBoundingBox::contains(const axisAlignedBoundingBox &box) {
    point boxOrigin = box.getOrigin();
    // Checks if the current box contains the upper left point and lower right point of the other box.
    return (this->contains(boxOrigin) and (this->contains(boxOrigin + point(box.length, box.height))));
}

// Checks if the current axisAlignedBoundingBox object contains a given point.
bool axisAlignedBoundingBox::contains(const point &point) {
    // Checks if the given point is within the horizontal and vertical boundaries of the box.
    return ((point.getX() <= origin.getX() + length) and (point.getX() >= origin.getX()) and (point.getY() <= origin.getY() + height) and (point.getY() >= origin.getY()));
}

// Overloaded equality operator to compare two axisAlignedBoundingBox objects.
bool axisAlignedBoundingBox::operator==(const axisAlignedBoundingBox &rhs) const {
    return origin == rhs.origin && length == rhs.length && height == rhs.height;
}

// Overloaded inequality operator to compare two axisAlignedBoundingBox objects.
bool axisAlignedBoundingBox::operator!=(const axisAlignedBoundingBox &rhs) const {
    return !(rhs == *this);
}

// Function to move the origin of the axisAlignedBoundingBox object by a given point.
void axisAlignedBoundingBox::move(const point &point) {
    this->origin.move(point);
}

