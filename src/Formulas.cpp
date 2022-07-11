//
// Created by thilo on 22.03.2022.
//

#include "Formulas.h"
#include <cmath>
#include <iostream>

struct Formulas::Line  {
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
    std::vector<std::vector<float>> A = {{p12.x-p11.x, -(p22.x-p21.x)} , {p12.y-p11.y, -(p22.y-p21.y)}};
    std::vector<float> b = {p11.x-p21.x, p11.y-p21.y};
    std::vector<float> x = gaussianElimination(A,b);
    if(x[0]>=0 && x[0] <= 1 && x[1]>=0 && x[1] <= 1) return true;
    return false;
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

bool Formulas::convexShapeIntersectLine( sf::ConvexShape &shape, sf::Vector2f p1, sf::Vector2f p2) {
    for(int i=1; i<=shape.getPointCount(); i++){
        if(lineIntersectLine(shape.getPoint(i),shape.getPoint((i+1)%shape.getPointCount()),p1, p2)) return true;
    }
    return false;
}

bool Formulas::convexShapeIntersectConvexShape(sf::ConvexShape &shape1, sf::ConvexShape &shape2) {
    for(int j=1; j<=shape1.getPointCount(); j++) {
        if(convexShapeIntersectLine(shape2,shape1.getPoint(j),shape1.getPoint((j+1)%shape1.getPointCount()))) return true;
    }
    return false;
}