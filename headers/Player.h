#include <SFML/Graphics.hpp>


class Player {
private:
    sf::ConvexShape player_shape;
    sf::Vector2f movement = {0,0};
    sf::Vector2f direction = {0,0};
public:
    Player();
    sf::ConvexShape getShape();
    sf::Vector2f* getMovement();
    sf::Vector2f getDirection();
    sf::Vector2f getPosition();
    void setPosition(sf::Vector2f);
    void rotate(double);
    float getRotation();
};

