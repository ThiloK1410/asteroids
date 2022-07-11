
#ifndef ASTEROIDS_FORMULAS_H
#define ASTEROIDS_FORMULAS_H

#include <SFML/Graphics.hpp>


struct Formulas {
public:
    struct Line;
    static void rotateVector(sf::Vector2f &,float);
    static float degToRad(float);
    static float radToDeg(float);
    static float getVectorLength(sf::Vector2f);
    static void normalizeVector(sf::Vector2f &);
    static sf::Vector2f multiplyVectorWithFactor(sf::Vector2f ,float);
    static bool convexShapeIntersectLine(sf::ConvexShape &,sf::Vector2f ,sf::Vector2f);
    static bool lineIntersectLine(sf::Vector2f,sf::Vector2f,sf::Vector2f,sf::Vector2f);
    static bool convexShapeIntersectConvexShape(sf::ConvexShape &, sf::ConvexShape &);
private:
    static std::vector<float> gaussianElimination(std::vector<std::vector<float>>,std::vector<float>);
};


#endif //ASTEROIDS_FORMULAS_H
