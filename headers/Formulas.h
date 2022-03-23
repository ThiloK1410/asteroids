
#ifndef ASTEROIDS_FORMULAS_H
#define ASTEROIDS_FORMULAS_H

#include <SFML/Graphics.hpp>


struct Formulas {
public:
    static sf::Vector2f rotateVector(sf::Vector2f,double);
    static float degToRad(float);
    static float radToDeg(float);
    static float getVectorLength(sf::Vector2f);
};


#endif //ASTEROIDS_FORMULAS_H
