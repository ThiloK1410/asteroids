#ifndef ASTEROIDS_ENGINE_H
#define ASTEROIDS_ENGINE_H

#include <SFMl/Graphics.hpp>


class Engine {
private:
    sf::Vector2f resolution;
    sf::RenderWindow window;
    static const unsigned int FPS = 60;
    static const sf::Time TimePerFrame;
public:
    Engine();
    void draw();
    void run();
    void input();
    void updatePlayer();
};


#endif //ASTEROIDS_ENGINE_H
