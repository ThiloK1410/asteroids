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
    sf::Vector2f screen_size = Engine::resolution;
    sf::Vector2f new_movement = *player.getMovement();
    sf::Vector2f new_position = player.getPosition();
    float factor_1 = 0.00000001;
    float max_speed = 5;
    sf::Vector2f scaledMovement ={player.getMovement()->x * factor_1, player.getMovement()->y * factor_1};
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
    if(Formulas::getVectorLength(*player.getMovement()) > max_speed){              //holding the speed below max_speed
        double factor = max_speed / Formulas::getVectorLength(*player.getMovement());

        new_movement.x = new_movement.x * factor;
        new_movement.y = new_movement.y * factor;
        *player.getMovement()=new_movement;
    }

    if ( new_position.x > screen_size.x && new_movement.x > 0) {
        new_position.x = 0;
    }
    if (new_position.x < 0 && new_movement.x < 0 ) {
        new_position.x = screen_size.x;
    }
    if (new_position.y > screen_size.y && new_movement.y > 0 ) {
        new_position.y = 0;
    }
    if (new_position.y < 0 && new_movement.y <0) {
        new_position.y = screen_size.y;
    }

    std::cout << "\r" << "player position : " << player.getPosition().x << "   " << player.getPosition().y ;

    player.setPosition(new_position+new_movement);
}
