//
// Created by Joeri on 11/22/2023.
//

#ifndef QUADTREE_POINT_H
#define QUADTREE_POINT_H


#include <ostream>

class point {
private:
    double x, y;

public:
    point(double x, double y);

    double getX() const;

    void setX(double x);

    double getY() const;

    void setY(double y);

    bool isLower(const point &point);

    bool isLeft(const point &point);

    friend std::ostream &operator<<(std::ostream &os, const point &point);

    bool operator==(const point &rhs) const;

    bool operator!=(const point &rhs) const;

    point operator+(const point &rhs) const;
};


#endif //QUADTREE_POINT_H
