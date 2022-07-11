//
// Created by thilo on 27.03.2022.
//

#include "Comet.h"
#include "Engine.h"
#include <time.h>
#include "Formulas.h"
#include "Engine.h"

Comet::Comet() {
    comet_shape.setPointCount(10);
    comet_shape.setPoint(0, sf::Vector2f(30, 0));
    comet_shape.setPoint(1, sf::Vector2f(50, 10));
    comet_shape.setPoint(2, sf::Vector2f(60, 20));
    comet_shape.setPoint(3, sf::Vector2f(50, 40));
    comet_shape.setPoint(4, sf::Vector2f(30, 40));
    comet_shape.setPoint(5, sf::Vector2f(20, 50));
    comet_shape.setPoint(6, sf::Vector2f(10, 50));
    comet_shape.setPoint(7, sf::Vector2f(0, 30));
    comet_shape.setPoint(8, sf::Vector2f(10, 10));
    comet_shape.setPoint(9, sf::Vector2f(20, 10));
    comet_shape.setOrigin(30, 25);
    comet_shape.setFillColor(sf::Color(128, 128, 128));
    comet_shape.setScale(2, 2);
    level = 0;
    setStartPos();
}

Comet::Comet(bool isLeft, Comet mother) {
    comet_shape.setPointCount(10);
    comet_shape.setPoint(0, sf::Vector2f(30, 0));
    comet_shape.setPoint(1, sf::Vector2f(50, 10));
    comet_shape.setPoint(2, sf::Vector2f(60, 20));
    comet_shape.setPoint(3, sf::Vector2f(50, 40));
    comet_shape.setPoint(4, sf::Vector2f(30, 40));
    comet_shape.setPoint(5, sf::Vector2f(20, 50));
    comet_shape.setPoint(6, sf::Vector2f(10, 50));
    comet_shape.setPoint(7, sf::Vector2f(0, 30));
    comet_shape.setPoint(8, sf::Vector2f(10, 10));
    comet_shape.setPoint(9, sf::Vector2f(20, 10));
    comet_shape.setOrigin(28, 25);
    comet_shape.setFillColor(sf::Color(128, 128, 128));
    level = mother.getLevel() + 1;
    position = mother.getPosition();
    direction = mother.getDirection();
    float divergeDegrees = 10;
    if (isLeft) Formulas::rotateVector(direction, -divergeDegrees);
    if (!isLeft) Formulas::rotateVector(direction, divergeDegrees);
    if (level == 1) comet_shape.setScale(1.5, 1.5);
    if (level == 2) comet_shape.setScale(1, 1);
}

void Comet::setStartPos() {     //set the position to a random point out of bounds
    int x = rand() % 4;
    const int directionStepCount = 20;
    if (x == 0) {                  //left
        float pos = rand() % static_cast<int>(Engine::resolution.y);
        position = sf::Vector2f{0, pos};
        direction = {static_cast<float>(rand() % directionStepCount + 1),
                     static_cast<float>((rand() % (directionStepCount * 2)) - directionStepCount)};
        Formulas::normalizeVector(direction);
    } else if (x == 1) {            //right
        float pos = rand() % static_cast<int>(Engine::resolution.y);
        position = sf::Vector2f{Engine::resolution.x, pos};
        direction = {static_cast<float>(-(rand() % directionStepCount + 1)),
                     static_cast<float>((rand() % (directionStepCount * 2)) - directionStepCount)};
        Formulas::normalizeVector(direction);
    } else if (x == 2) {            //top
        float pos = rand() % static_cast<int>(Engine::resolution.x);
        position = sf::Vector2f{pos, 0};
        direction = {static_cast<float>((rand() % (directionStepCount * 2)) - directionStepCount),
                     static_cast<float>(rand() % directionStepCount + 1)};
        Formulas::normalizeVector(direction);
    } else if (x == 3) {            //bottom
        float pos = rand() % static_cast<int>(Engine::resolution.x);
        position = sf::Vector2f{pos, Engine::resolution.y};
        direction = {static_cast<float>((rand() % (directionStepCount * 2)) - directionStepCount),
                     static_cast<float>(-(rand() % directionStepCount + 1))};
        Formulas::normalizeVector(direction);

    }
}

int Comet::getLevel() {
    return level;
}

sf::Vector2f Comet::getPosition() {
    return position;
}

sf::Vector2f Comet::getDirection() {
    return direction;
}

sf::ConvexShape Comet::getShape() {
    return comet_shape;
}

void Comet::doStep() {
    float speed = 5;
    position += Formulas::multiplyVectorWithFactor(direction, speed);
    sf::Vector2f screen_size = Engine::resolution;
    if (position.x > screen_size.x + comet_shape.getOrigin().x * comet_shape.getScale().x && direction.x > 0) {
        position.x = -comet_shape.getOrigin().x * comet_shape.getScale().x;
    }
    if (position.x < -comet_shape.getOrigin().x * comet_shape.getScale().x && direction.x < 0) {
        position.x = screen_size.x + comet_shape.getOrigin().x * comet_shape.getScale().x;
    }
    if (position.y > screen_size.y + comet_shape.getOrigin().y * comet_shape.getScale().y && direction.y > 0) {
        position.y = -comet_shape.getOrigin().y * comet_shape.getScale().y;
    }
    if (position.y < -comet_shape.getOrigin().y * comet_shape.getScale().y && direction.y < 0) {
        position.y = screen_size.y + comet_shape.getOrigin().y * comet_shape.getScale().y;
    }
    comet_shape.setPosition(position);
}


