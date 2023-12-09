//
// Created by Joeri on 12/9/2023.
//

#ifndef QUADTREE_RECTANGLEOBJECT_H
#define QUADTREE_RECTANGLEOBJECT_H


struct RectangleObject {

    sf::RectangleShape shape;
    axisAlignedBoundingBox boundingBox;

    void move(point &point){
        boundingBox.move(point);
        shape.move({point.getX(), point.getY()});
    };
};

#endif //QUADTREE_RECTANGLEOBJECT_H
