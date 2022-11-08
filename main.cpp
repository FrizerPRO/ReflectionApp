#include <SFML/Graphics.hpp>
#include <iostream>
#include<cmath>
#include "Trace/Trace.h"
#include "Vector2D/Vector2D.h"
int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
    std::vector<sf::Shape *> shapes;
    sf::CircleShape *circle = new sf::CircleShape(100);
    circle->setPosition(0, 0);
    shapes.push_back(circle);
    sf::CircleShape *circle1 = new sf::CircleShape(100);
    circle1->setPosition(400, 400);
    shapes.push_back(circle1);
    circle->setFillColor(sf::Color::Green);
    circle1->setFillColor(sf::Color::Blue);
    while (window.isOpen()) {
        Trace trace(window, 5);
        trace.setPosition(sf::Vector2f(200, 200));
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //circle->move(sf::Vector2f(0.01f, 0.01f));
        trace.TrackMouse();
        window.clear();
        window.draw(*circle);
        window.draw(*circle1);
        trace.Draw(shapes);
        window.display();
    }
    return 0;
}