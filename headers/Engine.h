#ifndef ASTEROIDS_ENGINE_H
#define ASTEROIDS_ENGINE_H

#include <SFMl/Graphics.hpp>


class Engine {
private:
    sf::Clock clock;
    sf::RenderWindow window;
    static const unsigned int FPS = 60;
public:
    inline static sf::Vector2f resolution = sf::Vector2f(1000,1000) ;
    Engine();
    void draw();
    void run();
    void input();
    void updatePlayer();
};


#endif //ASTEROIDS_ENGINE_H
