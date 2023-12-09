//
// Created by Joeri on 11/22/2023.
//

#include "point.h"

point::point(float x, float y) : x(x), y(y) {}

float point::getX() const {
    return x;
}

void point::setX(float x) {
    point::x = x;
}

float point::getY() const {
    return y;
}

void point::setY(float y) {
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
    float newX = this->x + rhs.x;
    float newY = this->y + rhs.y;
    return {newX,newY};
}

bool point::isLower(const point &point) {
    return (this->y > point.y);
}

bool point::isLeft(const point &point) {
    return (this->x < point.x);
}

void point::move(const point &point) {
    this->x += point.getX();
    this->y += point.getY();
}
