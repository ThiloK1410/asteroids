//
// Created by thilo on 22.03.2022.
//

#include "Formulas.h"
#include <cmath>
#include <iostream>

struct Line {
    sf::Vector2f position;
    sf::Vector2f direction;

    Line(sf::Vector2f pos1, sf::Vector2f pos2) {
        position = pos1;
        direction = pos2 - pos1;
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

std::vector<float> Formulas::gaussianElimination(std::vector<std::vector<float>> A, std::vector<float> b) {  //Ax = b : returns x
    if(!(A.size()==b.size() && b.size()==A[0].size()))
        std::cout << "@gaussianElimination: input not usable for gaussian elimination" << std::endl;

    std::vector<float> x (b.size());

    for(int i = 0;i<A.size();i++) {  //changing rows so the diagonal is !=0
        if(A[i][i]==0) {
            for(int j = 0;j<A.size();j++) {
                if(A[j][i]!=0) {
                    std::vector<float> temp = A[i];
                    A[i] = A[j];
                    A[j] = temp;
                }
            }
        }
    }

    for(int i = 0;i<A.size();i++) { //iterates through rows
        float x1 = A[i][i];
        for( int j = i;j<A.size();j++) { // iterates through columns starting at the diagonal
            A[i][j] = A[i][j] / x1;  // bringing diagonal down to 1
        }
        b[i] = b[i] / x1;
        for(int j = 0;j<A.size();j++) { //iterates through rows except for A[i]  --
            if(j==i) continue;
            float x2 = A[j][i];
            for(int k=0;k<A.size();k++){ //iterates through columns
                A[j][k] = A[j][k] - x2*A[i][k];
            }
            b[j] = b[j] - x2*b[i];
        }
    }

    x = b;
    return x;
}

