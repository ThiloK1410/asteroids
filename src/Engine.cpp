#include "Engine.h"
#include "Player.h"
#include "Formulas.h"
#include <iostream>

const sf::Time Engine::TimePerFrame = sf::seconds(1.f/FPS);
Player player;

bool left,right,up,down;

Engine::Engine() {
    resolution = sf::Vector2f(800,600);
    window.create(sf::VideoMode(resolution.x,resolution.y), "Asteroids", sf::Style::Default);
    window.setFramerateLimit(FPS);
}

void Engine::run() {        //main loop, runs until window is closed
    while (window.isOpen()) {
        draw();
        input();
        updatePlayer();
    }
}

void Engine::draw() {  //everything that needs to be displayed has to be mentioned here
    window.clear(sf::Color::Black); //background color

    window.draw(player.getShape());

    window.display();
}

void Engine::input() {
    sf::Event event{};

    while (window.pollEvent(event)) {

        if (event.type == sf::Event::Closed) window.close();

        if (event.type == sf::Event::KeyPressed) {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                up = true;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                left = true;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                right = true;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                down = true;
            }
        }
        if (event.type == sf::Event::KeyReleased) {
            if(event.key.code == sf::Keyboard::Left){
                left = false;
            }
            if(event.key.code == sf::Keyboard::Right) {
                right = false;
            }
            if(event.key.code == sf::Keyboard::Up) {
                up = false;
            }
            if(event.key.code == sf::Keyboard::Down) {
                down = false;
            }
        }
    }
}

void Engine::updatePlayer() {
    float factor = 0.0000000001;
    sf::Vector2f scaledMovement ={player.getMovement()->x*factor,player.getMovement()->y*factor};
    if(left) {
        player.rotate(-5);
    }
    if(right) {
        player.rotate(5);
    }
    if(up) {
        sf::Vector2f x = player.getDirection() + scaledMovement;
        *player.getMovement() = *player.getMovement() + x;
    }
    if(down) {
        sf::Vector2f x = player.getDirection() - scaledMovement;
        *player.getMovement() = *player.getMovement() + x;
    }
    player.setPosition(player.getPosition()+*player.getMovement());
}
