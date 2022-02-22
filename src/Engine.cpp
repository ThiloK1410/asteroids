#include "Engine.h"

const sf::Time Engine::TimePerFrame = sf::seconds(1.f/FPS);

Engine::Engine() {
    resolution = sf::Vector2f(800,600);
    window.create(sf::VideoMode(resolution.x,resolution.y), "Asteroids", sf::Style::Default);
    window.setFramerateLimit(FPS);
}

void Engine::run() {        //main loop, runs until window is closed
    while (window.isOpen()) {
        draw();
        input();
    }
}

void Engine::draw() {  //everything that needs to be displayed has to be mentioned here
    window.clear(sf::Color::White); //background color

    window.display();
}

void Engine::input() {
    sf::Event event{};

    while (window.pollEvent(event)) {

        if (event.type == sf::Event::Closed) window.close();

        if (event.type == sf::Event::KeyPressed) {



        }
    }
}