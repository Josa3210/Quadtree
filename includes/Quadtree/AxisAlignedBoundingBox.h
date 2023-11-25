//
// Created by Joeri on 11/22/2023.
//

#ifndef QUADTREE_AXISALIGNEDBOUNDINGBOX_H
#define QUADTREE_AXISALIGNEDBOUNDINGBOX_H

#include <tuple>
#include <set>
#include <ostream>
#include "Point.h"

// This class represents an axis-aligned bounding box
// In a 2D problem, this is simply a rectangle whose sides are
// parallel to the X- and Y-axis
class AxisAlignedBoundingBox {
    friend class QuadTree;
private:
    Point origin;                           // The center of the rectangle
    double length;                          // The half length of the rectangle (x-axis)
    double height;                          // The half height of the rectangle (y-axis)

public:
    // Constructor
    AxisAlignedBoundingBox(Point origin, double length, double height);
    AxisAlignedBoundingBox();

    // Getters and setters
    const Point &getOrigin() const;

    void setOrigin(const Point &newOrigin);

    double getLength() const;

    void setLength(double newLength);

    double getHeight() const;

    void setHeight(double newHeight);

    bool collides(const AxisAlignedBoundingBox &two);

    bool contains(const AxisAlignedBoundingBox &box);
    bool contains(const Point &point);

    friend std::ostream &operator<<(std::ostream &os, const AxisAlignedBoundingBox &box);

    // This friend function (A free function that can access private fields) should check if two AABBs overlap
    // It returns true if there is overlap, false if there isn’t
    friend bool collides(
            const AxisAlignedBoundingBox &one,
            const AxisAlignedBoundingBox &two
    );

    bool operator==(const AxisAlignedBoundingBox &rhs) const;

    bool operator!=(const AxisAlignedBoundingBox &rhs) const;
};


#endif //QUADTREE_AXISALIGNEDBOUNDINGBOX_H
