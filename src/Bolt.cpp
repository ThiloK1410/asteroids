
#include "Bolt.h"
#include "Engine.h"
#include <cmath>
#include <iostream>

Bolt::Bolt(sf::Vector2f pos,sf::Vector2f dir) {
    player_shape.setPointCount(4);
    player_shape.setPoint(0,sf::Vector2f(0,0));
    player_shape.setPoint(1,sf::Vector2f(3,0));
    player_shape.setPoint(2,sf::Vector2f(3,20));
    player_shape.setPoint(3,sf::Vector2f(0,20));
    player_shape.setOrigin(2,0);
    player_shape.setRotation(atanf(dir.y/dir.x)*180/M_PI+90);
    boltSpeed = 15;
    position = pos;
    direction = dir;
}

sf::ConvexShape Bolt::getShape() {
    return player_shape;
}

void Bolt::doStep() {
    position+=direction*boltSpeed;
    player_shape.setPosition(position);
    if(position.x < -20 ||position.x>Engine::resolution.x+20||position.y < -20 ||position.y>Engine::resolution.y+20) isOutOfBounds = true;
}

void Bolt::setPosition(sf::Vector2f pos) {
    position = pos;
}

sf::Vector2f Bolt::getPosition() {
    return position;
}

bool Bolt::outOfBounds() {
    return isOutOfBounds;
}

sf::Vector2f Bolt::getDirection() {
    return direction;
}
