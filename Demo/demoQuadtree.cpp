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
    axisAlignedBoundingBox windowBox = axisAlignedBoundingBox(0, 0, windowWidth, windowHeight);


    // Create text object
    sf::Font openSans;
    openSans.loadFromFile("D:\\_Opslag\\Programmeren\\C++\\Quadtree\\res\\OpenSans-Medium.ttf");

    sf::Text my_text = sf::Text(openSans);
    my_text.setPosition({50, 50});
    my_text.setFillColor(sf::Color::White);
    my_text.setCharacterSize(20);


    // Create rectangles
    int n = 100;
    int speed = 30;
    float rectSize = 10;

    // Timing
    long frames = 0;
    unsigned int seconds = 10;
    unsigned int fps = 30;
    unsigned int maxFrames = seconds * fps;

    long totalCollisions = 0;

    std::vector<RectangleObject> rectangles;
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

    // Create window
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

        // Create quadtree for storing objects
        Quadtree<sf::RectangleShape> qt = Quadtree<sf::RectangleShape>(windowBox, 5);

        // Move the rectangles
        for (auto &rectangle: rectangles) {
            // Update position
            float deltaX = rand() % speed - speed / 2;
            float deltaY = rand() % speed - speed / 2;

            point deltaPoint = point(deltaX, deltaY);
            // check if position is not out of bounds
            auto testBox = axisAlignedBoundingBox(rectangle.boundingBox);
            testBox.move(deltaPoint);
            while (!windowBox.contains(testBox)) {
                deltaX = rand() % speed - speed / 2;
                deltaY = rand() % speed - speed / 2;
                testBox = axisAlignedBoundingBox(rectangle.boundingBox);
                deltaPoint = point(deltaX, deltaY);
                testBox.move(deltaPoint);
            }
            rectangle.move(deltaPoint);

            // Insert new object in qt
            object<sf::RectangleShape> newObj = object<sf::RectangleShape>(rectangle.boundingBox, rectangle.shape);
            qt.insert(newObj);
        }

        // Check for collisions
        int collisions = 0;
        for (auto &rectangle: rectangles) {
            axisAlignedBoundingBox box = rectangle.boundingBox;
            float newOriginX = box.getOrigin().getX() - 50;
            float newOriginY = box.getOrigin().getY() - 50;
            float newLength = box.getLength() + 50;
            float newHeigth = box.getHeight() + 50;

            axisAlignedBoundingBox queryRegion = axisAlignedBoundingBox(newOriginX, newOriginY, newLength, newHeigth);
            auto otherRectangles = qt.query_region(queryRegion);
            for (auto &otherRect: otherRectangles) {
                collisions++;
                if (rectangle.boundingBox != otherRect.box && collides(rectangle.boundingBox, otherRect.box)) {
                    rectangle.shape.setFillColor(sf::Color::Red);
                    sf::RectangleShape rect = otherRect.value;
                    rect.setFillColor(sf::Color::Red);
                    break;
                } else {
                    rectangle.shape.setFillColor(sf::Color::Green);
                }
            }
        }

        // Calculate total collision calculations
        totalCollisions += collisions;
        my_text.setString("Total collision calculations: " + std::to_string(totalCollisions));


        window.clear();
        for (const auto &rectangle: rectangles) {
            window.draw(rectangle.shape);
        }
        window.draw(my_text);
        window.display();

        frames += 1;
        while (frames > maxFrames) {
            window.clear();
            my_text.setPosition({(float) windowWidth / 2 - my_text.getGlobalBounds().width / 2, (float) windowHeight / 2 - my_text.getGlobalBounds().height / 2});
            my_text.setCharacterSize(50);
            window.draw(my_text);
            window.display();
        }
    }

    return 0;
}
