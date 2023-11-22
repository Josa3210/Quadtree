//
// Created by Joeri on 11/22/2023.
//

#ifndef QUADTREE_POINT_H
#define QUADTREE_POINT_H


#include <ostream>

class Point {
private:
    double x, y;

public:
    Point(double x, double y);

    double getX() const;

    void setX(double x);

    double getY() const;

    void setY(double y);

    friend std::ostream &operator<<(std::ostream &os, const Point &point);

    bool operator==(const Point &rhs) const;

    bool operator!=(const Point &rhs) const;

    bool operator<(const Point &rhs) const;

    bool operator>(const Point &rhs) const;

    bool operator<=(const Point &rhs) const;

    bool operator>=(const Point &rhs) const;

    Point operator+(const Point &rhs) const;
};


#endif //QUADTREE_POINT_H
