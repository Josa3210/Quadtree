#ifndef QUADTREE_AXISALIGNEDBOUNDINGBOX_H
#define QUADTREE_AXISALIGNEDBOUNDINGBOX_H

#include <tuple>      // Include tuple for storing coordinates
#include <set>        // Include set for storing and checking collisions
#include <ostream>    // Include ostream for operator<< overloading
#include "point.h"    // Include the Point class for coordinate handling

// This class represents an axis-aligned bounding box
// In a 2D problem, this is simply a rectangle whose sides are
// parallel to the X- and Y-axis
class axisAlignedBoundingBox {
    friend class QuadTree;    // Friend class for accessing private members of quadtree
private:
    point origin;             // The UpperLeft of the rectangle
    float length;             // The length of the rectangle (x-axis)
    float height;             // The height of the rectangle (y-axis)

public:
    // Constructor to initialize an AxisAlignedBoundingBox object with given parameters
    axisAlignedBoundingBox(point origin, float length, float height);

    // Default constructor to create an empty AxisAlignedBoundingBox object
    axisAlignedBoundingBox();

    // Constructor to initialize an AxisAlignedBoundingBox object with given parameters
    axisAlignedBoundingBox(float originX, float originY, float length, float height);

    // Getter function to retrieve the origin point of the bounding box
    [[nodiscard]] const point &getOrigin() const;

    // Setter function to set the origin point of the bounding box
    void setOrigin(const point &newOrigin);

    // Getter function to retrieve the length of the bounding box
    [[nodiscard]] float getLength() const;

    // Setter function to set the length of the bounding box
    void setLength(float newLength);

    // Getter function to retrieve the height of the bounding box
    [[nodiscard]] float getHeight() const;

    // Setter function to set the height of the bounding box
    void setHeight(float newHeight);

    // Function to check if the bounding box collides with another bounding box
    bool collides(const axisAlignedBoundingBox &two) const;

    // Function to check if the bounding box contains another bounding box
    bool contains(const axisAlignedBoundingBox &box);

    // Function to check if the bounding box contains a point
    bool contains(const point &point);

    // Function to move the bounding box to a new position
    void move(const point &point);

    // Friend function to overload the << operator for printing an AxisAlignedBoundingBox object
    friend std::ostream &operator<<(std::ostream &os, const axisAlignedBoundingBox &box);

    // Friend function to check if two AxisAlignedBoundingBoxes overlap
    friend bool collides(const axisAlignedBoundingBox &one, const axisAlignedBoundingBox &two);

    // Overload the == operator to compare two AxisAlignedBoundingBox objects for equality
    bool operator==(const axisAlignedBoundingBox &rhs) const;

    // Overload the != operator to compare two AxisAlignedBoundingBox objects for inequality
    bool operator!=(const axisAlignedBoundingBox &rhs) const;
};

#endif //QUADTREE_AXISALIGNEDBOUNDINGBOX_H