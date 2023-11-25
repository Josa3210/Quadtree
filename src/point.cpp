//
// Created by Joeri on 11/22/2023.
//

#include "point.h"

point::point(double x, double y) : x(x), y(y) {}

double point::getX() const {
    return x;
}

void point::setX(double x) {
    point::x = x;
}

double point::getY() const {
    return y;
}

void point::setY(double y) {
    point::y = y;
}

bool point::operator==(const point &rhs) const {
    return x == rhs.x &&
           y == rhs.y;
}

bool point::operator!=(const point &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const point &point) {
    os << "point(" << point.x << ", " << point.y << ")";
    return os;
}

point point::operator+(const point &rhs) const{
    double newX = this->x + rhs.x;
    double newY = this->y + rhs.y;
    return {newX,newY};
}

bool point::isLower(const point &point) {
    return (this->y > point.y);
}

bool point::isLeft(const point &point) {
    return (this->x < point.x);
}
