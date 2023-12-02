//
// Created by Joeri on 11/27/2023.
//

#include <SFML/Graphics.hpp>
#include <windows.h>


int main() {
    // create the window
    unsigned int windowWidth = 2000;
    unsigned int windowHeight = 1200;

    // Create circles
    int n = 10;
    std::vector circleVec = std::vector<sf::CircleShape>();
    std::vector posVec = std::vector<sf::Vector2f>();
    for (int i = 0; i < n; i++) {
        sf::Vector2f randpoint = sf::Vector2f(rand() % windowWidth, rand() % windowHeight);
        sf::CircleShape circle = sf::CircleShape();
        circle.setPosition(randpoint);
        circle.setRadius(10);
        circleVec.push_back(circle);
        posVec.push_back(randpoint);
    }


    sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}), "Window1");

    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        //Draw circles
        for (const sf::CircleShape& circle : circleVec){
            window.draw(circle);
        }


        // end the current frame
        window.display();
    }

    return 0;
}

void updatePos(const std::vector<sf::Vector2f>& vector1) {

}
