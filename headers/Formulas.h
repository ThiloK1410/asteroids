
#ifndef ASTEROIDS_FORMULAS_H
#define ASTEROIDS_FORMULAS_H

#include <SFML/Graphics.hpp>


struct Formulas {
public:
    static void rotateVector(sf::Vector2f &,float);
    static float degToRad(float);
    static float radToDeg(float);
    static float getVectorLength(sf::Vector2f);
    static void normalizeVector(sf::Vector2f &);
    static sf::Vector2f multiplyVectorWithFactor(sf:: Vector2f ,float);
    static bool lineIntersectLine(sf::Vector2f,sf::Vector2f,sf::Vector2f,sf::Vector2f);
};


#endif //ASTEROIDS_FORMULAS_H
