//
// Created by Joeri on 11/22/2023.
//

#ifndef QUADTREE_POINT_H
#define QUADTREE_POINT_H


#include <ostream>

class point {
private:
    float x, y;

public:
    point(float x, float y);

    float getX() const;

    void setX(float x);

    float getY() const;

    void setY(float y);

    bool isLower(const point &point);

    bool isLeft(const point &point);

    void move(const point &point);

    friend std::ostream &operator<<(std::ostream &os, const point &point);

    bool operator==(const point &rhs) const;

    bool operator!=(const point &rhs) const;

    point operator+(const point &rhs) const;
};


#endif //QUADTREE_POINT_H
