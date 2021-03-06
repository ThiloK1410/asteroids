#include "Engine.h"
#include "Player.h"
#include "Bolt.h"
#include "Formulas.h"
#include <iostream>
#include "Comet.h"


Player player;
sf::Vector2f boltPos = {player.getPosition().x + 50, player.getPosition().y};
std::vector<Bolt> boltList;
std::vector<Comet> cometList;

bool left, right, up, down, space;

Engine::Engine() {
    //resolution = sf::Vector2f(1000,1000);
    window.create(sf::VideoMode(resolution.x, resolution.y), "Asteroids", sf::Style::Default);
    window.setFramerateLimit(FPS);
}

void Engine::run() {        //main loop, runs until window is closed

    while (window.isOpen()) {
        draw();
        input();
        updatePlayer();
        //checkCollision();
        for (int i = 0; i < boltList.size(); i++) {
            boltList[i].doStep();
            if (boltList[i].outOfBounds()) {
                boltList.erase(boltList.cbegin() + i);
            }
        }
        for (int i = 0; i < cometList.size(); i++) {
            cometList[i].doStep();
        }
    }
}

void Engine::draw() {  //everything that needs to be displayed has to be mentioned here
    window.clear(sf::Color::Black); //background color

    window.draw(player.getShape());
    for (int i = 0; i < boltList.size(); i++) {
        window.draw(boltList[i].getShape());
    }
    for (int i = 0; i < cometList.size(); i++) {
        window.draw(cometList[i].getShape());
    }

    window.display();
}

void Engine::input() {
    sf::Event event{};

    while (window.pollEvent(event)) {

        if (event.type == sf::Event::Closed) window.close();

        if (event.type == sf::Event::KeyPressed) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                up = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                space = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                left = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                right = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                down = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
                cometList.emplace_back(new Comet());
            }
        }
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Left) {
                left = false;
            }
            if (event.key.code == sf::Keyboard::Space) {
                space = false;
            }
            if (event.key.code == sf::Keyboard::Right) {
                right = false;
            }
            if (event.key.code == sf::Keyboard::Up) {
                up = false;
            }
            if (event.key.code == sf::Keyboard::Down) {
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
    float max_speed = 8;
    float brake_strength = 0.4;
    float fireRate = 0.2;
    sf::Vector2f scaledMovement = {player.getMovement()->x * factor_1, player.getMovement()->y * factor_1};


    if (left) {
        player.rotate(-5);
    }
    if (right) {
        player.rotate(5);
    }
    if (up) {
        sf::Vector2f x = player.getDirection() + scaledMovement;
        *player.getMovement() = *player.getMovement() + x;
    }
    if (down) {
        double brake_factor =
                (Formulas::getVectorLength(new_movement) - brake_strength) / Formulas::getVectorLength(new_movement);
        new_movement.x *= brake_factor;
        new_movement.y *= brake_factor;
        *player.getMovement() = new_movement;
    }
    if (space) {
        sf::Time boltCooldown = clock.getElapsedTime();
        if (boltCooldown.asSeconds() > fireRate) {
            clock.restart();
            Bolt bolt(player.getPosition(), player.getDirection());
            boltList.push_back(bolt);
        }
    }

    //holding the speed below max_speed
    if (Formulas::getVectorLength(*player.getMovement()) > max_speed) {
        double factor = max_speed / Formulas::getVectorLength(*player.getMovement());
        new_movement.x = new_movement.x * factor;
        new_movement.y = new_movement.y * factor;
        *player.getMovement() = new_movement;
    }

    if (new_position.x > screen_size.x && new_movement.x > 0) {
        new_position.x = 0;
    }
    if (new_position.x < 0 && new_movement.x < 0) {
        new_position.x = screen_size.x;
    }
    if (new_position.y > screen_size.y && new_movement.y > 0) {
        new_position.y = 0;
    }
    if (new_position.y < 0 && new_movement.y < 0) {
        new_position.y = screen_size.y;
    }

    player.setPosition(new_position + new_movement);
}

void Engine::checkCollision() {
    for(int i=0; i<boltList.size(); i++){
        for(int j=0; j<cometList.size(); j++){
            sf::ConvexShape x = boltList[i].getShape();
            sf::ConvexShape y = cometList[j].getShape();
            if(Formulas::convexShapeIntersectConvexShape(x,y)) {
                auto itBolt = boltList.cbegin();
                auto itComet = cometList.cbegin();
                boltList.erase(itBolt+i);
                cometList.erase(itComet+j);
            }
        }
    }
}

