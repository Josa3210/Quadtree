//
// Created by Joeri on 11/27/2023.
//

#include "SFML/Graphics.hpp"
#include <windows.h>
#include <cmath>
#include "axisAlignedBoundingBox.h"
#include "point.h"
#include "quadTree.h"
#include "RectangleObject.h"

point randPoint(int speed);

int main(int argc, char *argv[]) {
    // create the window
    unsigned int windowWidth = 2000;
    unsigned int windowHeight = 1200;
    unsigned int offset = 100;
    axisAlignedBoundingBox windowBox = axisAlignedBoundingBox(0, offset, windowWidth, windowHeight - offset);

    // Create text object
    sf::Font openSans;
    openSans.loadFromFile("D:\\_Opslag\\Programmeren\\C++\\Quadtree\\res\\OpenSans-Medium.ttf");

    // Create text objects for displaying total number of collisions in the Quadtree and normal collision detection
    sf::Text txt_totalColsQt = sf::Text(openSans);
    txt_totalColsQt.setPosition({50, 10});
    txt_totalColsQt.setFillColor(sf::Color::White);
    txt_totalColsQt.setCharacterSize(25);

    sf::Text txt_totalColsNormal = sf::Text(openSans);
    txt_totalColsNormal.setPosition({600, 10});
    txt_totalColsNormal.setFillColor(sf::Color::White);
    txt_totalColsNormal.setCharacterSize(25);

    // Create text objects for displaying the number of columns in the Quadtree and normal collision detection
    sf::Text txt_colsQt = sf::Text(openSans);
    txt_colsQt.setPosition({50, 50});
    txt_colsQt.setFillColor(sf::Color::White);
    txt_colsQt.setCharacterSize(25);

    sf::Text txt_colsNormal = sf::Text(openSans);
    txt_colsNormal.setPosition({600, 50});
    txt_colsNormal.setFillColor(sf::Color::White);
    txt_colsNormal.setCharacterSize(25);

    // Create text object for displaying the percentage of collisions avoided by using the Quadtree
    sf::Text txt_percentageQt = sf::Text(openSans);
    txt_percentageQt.setFillColor(sf::Color::White);
    txt_percentageQt.setCharacterSize(50);

    // Default values
    int n = 30;
    int speed = 50;
    float rectSize = 30;
    unsigned int fps = 30;

    // Get values from arguments
    if (strcmp(argv[1], "slow") == 0) {
        n = 9;
        speed = 50;
        rectSize = 60;
        fps = 1;
    } else if (strcmp(argv[1], "fast") == 0) {
        n = 100;
        speed = 10;
        rectSize = 10;
        fps = 30;
    }
    // Timing
    long frames = 0;
    unsigned int seconds = 10;
    unsigned int maxFrames = seconds * fps;

    float collBoxSide = 2.f * rectSize;

    // Initialize variables for keeping track of collisions
    int totalCollisionsQt = 0;
    int totalCollisionsNormal = 0;
    int collisionCalculationsQt = 0;
    int collisionCalculationsNormal = 0;

    std::vector<RectangleObject> rectangles;
    std::vector<sf::RectangleShape> collisionBoxes;
    // Create squares
    for (int i = 0; i < n; i++) {
        RectangleObject newRectangle;
        float randX = rand() % (windowWidth - 200) + 100;
        float randY = rand() % (windowHeight - offset - 200) + 100;

        // Set the size and position of the rectangle
        newRectangle.shape.setSize({rectSize, rectSize});
        newRectangle.shape.setPosition({randX, randY});

        // Set the bounding box of the rectangle
        newRectangle.boundingBox = axisAlignedBoundingBox({randX, randY}, rectSize, rectSize);

        // Calculate new origin
        float collBoxX = randX - collBoxSide / 2;
        float collBoxY = randY - collBoxSide / 2;

        // Set the collision shape of the bounding box
        sf::RectangleShape collisionShape = sf::RectangleShape({rectSize + collBoxSide, rectSize + collBoxSide});
        collisionShape.setPosition({collBoxX, collBoxY});
        collisionShape.setFillColor(sf::Color::Transparent);
        collisionShape.setOutlineColor(sf::Color::Yellow);
        collisionShape.setOutlineThickness(1);
        newRectangle.collisionShape = collisionShape;

        // Set the collision box around the bounding box
        newRectangle.collisionBox = axisAlignedBoundingBox({collBoxX, collBoxY}, rectSize + collBoxSide, rectSize + collBoxSide);

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
            // Create a temporary testbox at
            auto testBox = rectangle.boundingBox;

            // Move the box
            point deltaPoint = randPoint(speed);
            testBox.move(deltaPoint);

            // As long as the box is not in the window, redo the process
            while (!windowBox.contains(testBox)) {
                testBox.move(deltaPoint * -1);
                deltaPoint = randPoint(speed);
                testBox.move(deltaPoint);
            }

            // At last, move the whole object
            rectangle.move(deltaPoint);

            // Reset the color off all the rectangles to green
            rectangle.shape.setFillColor(sf::Color::Green);

            // Insert new object in qt
            object<sf::RectangleShape> newObj = object<sf::RectangleShape>(rectangle.boundingBox, rectangle.shape);
            qt.insert(newObj);
        }

        // Check for collisions using Quadtree
        for (auto &rectangle: rectangles) {
            // Get collisionBox from the rectangle item
            axisAlignedBoundingBox queryRegion = rectangle.collisionBox;

            // Query the Quadtree for other rectangles that intersect with the query region
            auto otherRectangles = qt.query_region(queryRegion);
            for (auto &otherRect: otherRectangles) {

                // Check if the box in the region isn't the box itself
                if (rectangle.boundingBox == otherRect.box) continue;

                // Increment the amount of calculations using the quadtree
                collisionCalculationsQt++;

                // Check if the current rectangle collides with the other rectangle
                if (collides(rectangle.boundingBox, otherRect.box)) {
                    // Get the other rectangle from the quadtree
                    sf::RectangleShape rect = otherRect.value;
                    // Set the color of both the rectangles to red if they collide
                    rectangle.shape.setFillColor(sf::Color::Red);
                    rect.setFillColor(sf::Color::Red);

                    // Increment the amount of collisions
                    totalCollisionsQt++;
                }
            }
        }

        // Check for collisionCalculationsQt
        for (auto &rectangle: rectangles) {
            for (auto &otherRect: rectangles) {
                if (&rectangle == &otherRect) continue;

                // Increment the amount of calculations using the normal method
                collisionCalculationsNormal++;

                // Check if the current rectangle collides with the other rectangle
                if (collides(rectangle.boundingBox, otherRect.boundingBox)) {
                    // Set the color of the rectangles to red if they collide
                    rectangle.shape.setFillColor(sf::Color::Red);
                    otherRect.shape.setFillColor(sf::Color::Red);

                    // Increment the amount of collisions
                    totalCollisionsNormal++;
                }
            }
        }

        // Calculate total collision calculations
        txt_totalColsQt.setString("Quadtree collision calculations: " + std::to_string(collisionCalculationsQt));
        txt_totalColsNormal.setString("Normal collision calculations: " + std::to_string(collisionCalculationsNormal));

        txt_colsQt.setString("Quadtree collisions: " + std::to_string(totalCollisionsQt/2));
        txt_colsNormal.setString("Normal collisions: " + std::to_string(totalCollisionsNormal/2));


        window.clear();

        // Draw al the rectangles
        for (const auto &rectangle: rectangles) {
            window.draw(rectangle.shape);
            window.draw(rectangle.collisionShape);
        }

        // Draw the different textfields
        window.draw(txt_totalColsQt);
        window.draw(txt_totalColsNormal);
        window.draw(txt_colsQt);
        window.draw(txt_colsNormal);

        // Show the window
        window.display();

        // calculate the fraction of calculations using the quadtree in relation with the normal amount of calculations
        double percentageQT = (double(collisionCalculationsQt) * 100 / double(collisionCalculationsNormal));

        // Convert to a string
        char str_percentage[5];
        sprintf(str_percentage, "%.2f", percentageQT);
        char pref[100] = "Fraction (%): ";
        txt_percentageQt.setString(strcat(strcat(pref, str_percentage)," %"));

        frames += 1;
        while (frames > maxFrames) {
            window.clear();

            int startingHeight = 250;
            int i = 1;
            int dist = 70;

            // Reposition the text fields
            txt_colsQt.setPosition({(float) windowWidth / 2 - txt_totalColsQt.getGlobalBounds().width / 2, static_cast<float>(startingHeight + (dist * i++))});
            txt_colsQt.setCharacterSize(50);

            txt_colsNormal.setPosition({(float) windowWidth / 2 - txt_totalColsQt.getGlobalBounds().width / 2, static_cast<float>(startingHeight + (dist * i++))});
            txt_colsNormal.setCharacterSize(50);

            i++;

            txt_totalColsQt.setPosition({(float) windowWidth / 2 - txt_totalColsQt.getGlobalBounds().width / 2, static_cast<float>(startingHeight + (dist * i++))});
            txt_totalColsQt.setCharacterSize(50);

            txt_totalColsNormal.setPosition({(float) windowWidth / 2 - txt_totalColsQt.getGlobalBounds().width / 2, static_cast<float>(startingHeight + (dist * i++))});
            txt_totalColsNormal.setCharacterSize(50);

            i++;

            txt_percentageQt.setPosition({(float) windowWidth / 2 - txt_totalColsQt.getGlobalBounds().width / 2, static_cast<float>(startingHeight + (dist * i++))});

            // Draw all the text field
            window.draw(txt_totalColsQt);
            window.draw(txt_totalColsNormal);
            window.draw(txt_percentageQt);
            window.draw(txt_colsQt);
            window.draw(txt_colsNormal);
            window.display();

            while (window.pollEvent(event)) {
                // "close requested" event: we close the window
                if (event.type == sf::Event::Closed) {
                    window.close();
                    frames = 0;
                }
                break;
            }
        }
    }

    return 0;
}

point randPoint(int speed) {
    auto deltaX = (float) (rand() % speed - speed / 2.);
    auto deltaY = (float) (rand() % speed - speed / 2.);
    return {deltaX, deltaY};
}


