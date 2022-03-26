//
// Created by thilo on 23.02.2022.
//

#include "Player.h"
#include "Formulas.h"
#include <cmath>

Player::Player() {
    player_shape.setPointCount(4);
    player_shape.setPoint(0,sf::Vector2f(10,0));
    player_shape.setPoint(1,sf::Vector2f(20,30));
    player_shape.setPoint(2,sf::Vector2f(10,20));
    player_shape.setPoint(3,sf::Vector2f(0,30));
    player_shape.setOrigin(10,15);
    player_shape.setPosition(sf::Vector2f(100,100));
    player_shape.setFillColor(sf::Color::White);
}

sf::ConvexShape Player::getShape() {
    return player_shape;
}

sf::Vector2f* Player::getMovement() {
    return &movement;
}

void Player::rotate(double degrees) {

player_shape.setRotation(player_shape.getRotation()+degrees);
direction.x = sin(getRotation()*M_PI/180);
direction.y = -cos(getRotation()*M_PI/180);
}

float Player::getRotation() {
    return player_shape.getRotation();
}
sf::Vector2f Player::getDirection() {
    return direction;
}
void Player::setPosition(sf::Vector2f x) {
    player_shape.setPosition(x);
}

sf::Vector2f Player::getPosition() {
    return player_shape.getPosition();
}
