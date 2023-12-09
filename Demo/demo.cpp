//
// Created by Joeri on 11/27/2023.
//

#include "SFML/Graphics.hpp"
#include <windows.h>
#include "axisAlignedBoundingBox.h"
#include "point.h"
#include "quadTree.h"
#include "RectangleObject.h"


int main() {
    // create the window
    unsigned int windowWidth = 2000;
    unsigned int windowHeight = 1200;

    // Create circles
    int n = 20;
    int speed = 50;
    unsigned int fps = 30;
    float rectSize = 50;
    std::vector rectangles = std::vector<RectangleObject>();

    // Create squares
    for (int i = 0; i < n; i++) {
        RectangleObject newRectangle;
        float randX = rand() % (windowWidth - 200) + 100;
        float randY = rand() % (windowHeight - 200) + 100;
        newRectangle.shape.setSize({rectSize, rectSize});
        newRectangle.shape.setPosition({randX, randY});
        newRectangle.boundingBox = axisAlignedBoundingBox({randX, randY}, rectSize, rectSize);
        rectangles.push_back(newRectangle);
    }


    sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}), "Window1");
    window.setFramerateLimit(fps);

    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        for (auto &rectangle: rectangles) {
            // Update position
            float deltaX = rand() % speed - speed / 2;
            float deltaY = rand() % speed - speed / 2;

            point deltaPoint = point(deltaX, deltaY);
            rectangle.move(deltaPoint);
        }

        for (auto &rectangle: rectangles) {
            // Check collisions
            for (auto &otherRect: rectangles) {
                if (&rectangle != &otherRect && collides(rectangle.boundingBox, otherRect.boundingBox)) {
                    rectangle.shape.setFillColor(sf::Color::Red);
                    otherRect.shape.setFillColor(sf::Color::Red);
                    break;
                } else {
                    rectangle.shape.setFillColor(sf::Color::Green);
                }
            }
        }

        window.clear();

        for (const auto &rectangle: rectangles) {
            window.draw(rectangle.shape);
        }

        window.display();



        // end the current frame
        window.display();

    }

    return 0;
}
