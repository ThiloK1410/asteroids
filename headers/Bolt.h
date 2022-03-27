//
// Created by thilo on 26.03.2022.
//

#ifndef ASTEROIDS_BOLT_H
#define ASTEROIDS_BOLT_H


#include <SFML/Graphics/ConvexShape.hpp>

class Bolt {
private:
    sf::ConvexShape player_shape;
    sf::Vector2f position;
    sf::Vector2f direction;
    float boltSpeed;
    bool isOutOfBounds = false;
public:
    bool outOfBounds();
    Bolt(sf::Vector2f,sf::Vector2f);
    sf::ConvexShape getShape();
    void doStep();
    void setPosition(sf::Vector2f);
    sf::Vector2f getPosition();

};


#endif //ASTEROIDS_BOLT_H
