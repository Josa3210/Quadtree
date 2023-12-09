//
// Created by Joeri on 11/22/2023.
//

#ifndef QUADTREE_AXISALIGNEDBOUNDINGBOX_H
#define QUADTREE_AXISALIGNEDBOUNDINGBOX_H

#include <tuple>
#include <set>
#include <ostream>
#include "point.h"

// This class represents an axis-aligned bounding box
// In a 2D problem, this is simply a rectangle whose sides are
// parallel to the X- and Y-axis
class axisAlignedBoundingBox {
    friend class QuadTree;
private:
    point origin;                           // The UpperLeft of the rectangle
    float length;                          // The length of the rectangle (x-axis)
    float height;                          // The height of the rectangle (y-axis)

public:
    // Constructor
    axisAlignedBoundingBox(point origin, float length, float height);
    axisAlignedBoundingBox();
    axisAlignedBoundingBox(float originX, float originY, float length, float height);

    // Getters and setters
    const point &getOrigin() const;

    void setOrigin(const point &newOrigin);

    float getLength() const;

    void setLength(float newLength);

    float getHeight() const;

    void setHeight(float newHeight);

    bool collides(const axisAlignedBoundingBox &two);
    bool contains(const axisAlignedBoundingBox &box);
    bool contains(const point &point);

    void move(const point &point);

    friend std::ostream &operator<<(std::ostream &os, const axisAlignedBoundingBox &box);

    // This friend function (A free function that can access private fields) should check if two AABBs overlap
    // It returns true if there is overlap, false if there isn’t
    friend bool collides(
            const axisAlignedBoundingBox &one,
            const axisAlignedBoundingBox &two
    );

    bool operator==(const axisAlignedBoundingBox &rhs) const;

    bool operator!=(const axisAlignedBoundingBox &rhs) const;
};


#endif //QUADTREE_AXISALIGNEDBOUNDINGBOX_H
