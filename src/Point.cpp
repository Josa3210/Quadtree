//
// Created by Joeri on 11/22/2023.
//

#include "Point.h"

Point::Point(double x, double y) : x(x), y(y) {}

double Point::getX() const {
    return x;
}

void Point::setX(double x) {
    Point::x = x;
}

double Point::getY() const {
    return y;
}

void Point::setY(double y) {
    Point::y = y;
}

bool Point::operator==(const Point &rhs) const {
    return x == rhs.x &&
           y == rhs.y;
}

bool Point::operator!=(const Point &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Point &point) {
    os << "(" << point.x << ", " << point.y << ")";
    return os;
}

Point Point::operator+(const Point &rhs) const{
    double newX = this->x + rhs.x;
    double newY = this->y + rhs.y;
    return {newX,newY};
}

bool Point::isLower(const Point &point) {
    return (this->y > point.y);
}

bool Point::isLeft(const Point &point) {
    return (this->x < point.x);
}
