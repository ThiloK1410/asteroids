//
// Created by thilo on 22.03.2022.
//

#include "Formulas.h"
#include <cmath>

sf::Vector2f Formulas::rotateVector(sf::Vector2f vector, double degrees) {
    sf::Vector2f out;
    out.x = vector.x* cos(degrees)-vector.y* sin(degrees);
    out.y = vector.x* sin(degrees)+vector.y* cos(degrees);
    return out;
}

float Formulas::degToRad(float x) {
    x = x*M_PI/180;
    return x;
}

float Formulas::radToDeg(float x) {
    x = x*180/M_PI;
    return x;
}

float Formulas::getVectorLength(sf::Vector2f x) {
    return sqrtf(powf(x.x,2)+powf(x.y,2));
}
