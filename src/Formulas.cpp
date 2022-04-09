//
// Created by thilo on 22.03.2022.
//

#include "Formulas.h"
#include <cmath>

struct Line {
    sf::Vector2f position;
    sf::Vector2f direction;

    Line(sf::Vector2f pos1, sf::Vector2f pos2) {
        position = pos1;
        direction = pos2 - pos1;
    }

    bool collisionWith(Line x) {
        // 1:   position
        // 2:   direction
        // 3:   x.position
        // 4:   x.direction
        // TODO: dividents cant be 0 so there needs to be a exception, also t,s needs to be initialized
        float intersectionX = (x.position.x - position.x) / direction.x +
                              ((x.position.y - position.y) * direction.x - (x.position.x - position.x) * direction.y) /
                              ((1 - (x.direction.y * direction.x) / (x.direction.x * direction.y)) *
                              (direction.x * direction.y));
        float intersectionY = ((x.position.y - position.y) * direction.x - (x.position.x-position.x)*direction.y) /
                                (-(x.direction.y*direction.x)+ (x.direction.x*direction.y));
        float t,s;
        if(t>=0 && t<=1 && s >=0 && s<=1) return true;
    }
};

void Formulas::rotateVector(sf::Vector2f &vector, float degrees) {
    sf::Vector2f out;
    out.x = vector.x * cos(degrees) - vector.y * sin(degrees);
    out.y = vector.x * sin(degrees) + vector.y * cos(degrees);
    vector = out;
}

float Formulas::degToRad(float x) {
    x = x * M_PI / 180;
    return x;
}

float Formulas::radToDeg(float x) {
    x = x * 180 / M_PI;
    return x;
}

float Formulas::getVectorLength(sf::Vector2f x) {
    return sqrtf(powf(x.x, 2) + powf(x.y, 2));
}

void Formulas::normalizeVector(sf::Vector2f &vector) {
    float x = getVectorLength(vector);
    vector.x /= x;
    vector.y /= x;
}

sf::Vector2f Formulas::multiplyVectorWithFactor(sf::Vector2f vector, float x) {
    vector.x *= x;
    vector.y *= x;
    return vector;
}

bool Formulas::lineIntersectLine(sf::Vector2f p11, sf::Vector2f p12, sf::Vector2f p21, sf::Vector2f p22) {
    Line first(p11, p12);
    Line second(p21, p22);
}

