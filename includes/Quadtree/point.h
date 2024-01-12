#ifndef QUADTREE_POINT_H
#define QUADTREE_POINT_H


#include <ostream>

class point {
private:
    // x-coordinate of the point
    float x;
    // y-coordinate of the point
    float y;

public:
    // Constructor for point class
    point(float x, float y);

    // Getter for x-coordinate
    float getX() const;

    // Setter for x-coordinate
    void setX(float x);

    // Getter for y-coordinate
    float getY() const;

    // Setter for y-coordinate
    void setY(float y);

    // Check if the point is lower than another point
    bool isLower(const point &point) const;

    // Check if the point is to the left of another point
    bool isLeft(const point &point) const;

    // Move the point by a given amount
    void move(const point &point);

    // Overloaded stream insertion operator
    friend std::ostream &operator<<(std::ostream &os, const point &point);

    // Overloaded equality operator
    bool operator==(const point &rhs) const;

    // Overloaded inequality operator
    bool operator!=(const point &rhs) const;

    // Overloaded addition operator
    point operator+(const point &rhs) const;

    // Overloaded multiplication operator
    point operator*(float factor) const;
};


#endif //QUADTREE_POINT_H
