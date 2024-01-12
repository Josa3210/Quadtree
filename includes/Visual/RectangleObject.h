//
// Created by Joeri on 12/9/2023.
//

#ifndef QUADTREE_RECTANGLEOBJECT_H
#define QUADTREE_RECTANGLEOBJECT_H


struct RectangleObject {

    sf::RectangleShape shape;
    axisAlignedBoundingBox boundingBox;

    sf::RectangleShape collisionShape;
    axisAlignedBoundingBox collisionBox;

    void move(point &point){
        boundingBox.move(point);
        collisionBox.move(point);
        shape.move({point.getX(), point.getY()});
        collisionShape.move({point.getX(), point.getY()});
    };
};

#endif //QUADTREE_RECTANGLEOBJECT_H
