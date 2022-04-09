
#ifndef ASTEROIDS_COMET_H
#define ASTEROIDS_COMET_H
#include <SFML/Graphics.hpp>
#include "Bolt.h"


class Comet {
private:
    sf::ConvexShape comet_shape;
    int level;                      //comet starts lvl 0 and level++ when it splits
    sf::Vector2f position;
    sf::Vector2f direction;
    void setStartPos();
public:
    Comet();
    Comet(bool, Comet);
    int getLevel();
    sf::ConvexShape getShape();
    sf::Vector2f getPosition();
    sf::Vector2f getDirection();
    void doStep();
    bool isHit(std::vector<Bolt>);
};


#endif //ASTEROIDS_COMET_H
