//
// Created by Joeri on 11/22/2023.
//

#include "point.h"

point::point(float x, float y) : x(x), y(y) {}

// Returns the x-coordinate of the point
float point::getX() const {
    return x;
}

// Sets the x-coordinate of the point to the given value
void point::setX(float x) {
    point::x = x;
}

// Returns the y-coordinate of the point
float point::getY() const {
    return y;
}

// Sets the y-coordinate of the point to the given value
void point::setY(float y) {
    point::y = y;
}

// Checks if two points are equal
bool point::operator==(const point &rhs) const {
    return x == rhs.x &&
           y == rhs.y;
}

// Checks if two points are not equal
bool point::operator!=(const point &rhs) const {
    return !(rhs == *this);
}

// Prints the point in the format "point(x, y)"
std::ostream &operator<<(std::ostream &os, const point &point) {
    os << "point(" << point.x << ", " << point.y << ")";
    return os;
}

// Adds two points together and returns the result
point point::operator+(const point &rhs) const{
    float newX = this->x + rhs.x;
    float newY = this->y + rhs.y;
    return {newX,newY};
}

// Checks if the current point is lower than the given point
bool point::isLower(const point &point) const {
    return (this->y >= point.y);
}

// Checks if the current point is to the left of the given point
bool point::isLeft(const point &point) const {
    return (this->x <= point.x);
}

// Moves the point by the given amount
void point::move(const point &point) {
    this->x += point.getX();
    this->y += point.getY();
}
// Multiplies the point with the given factor
point point::operator*(const float factor) const {
    return {this->x*factor, this->y*factor};
}
