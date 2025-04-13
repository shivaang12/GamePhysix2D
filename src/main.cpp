
#include <SFML/Graphics.hpp>
#include <iostream>

#include "advent/world.hpp"
#include "advent/controller.hpp"
#include "advent/game.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({1280, 960}), "Advent - SFML");

    // Defining Lambda function for closing the window
    const auto onClose = [&window](const sf::Event::Closed &) { window.close(); };

    // Framerate Limits
    window.setFramerateLimit(60);

    advent::Game game;
    game.initialize();

    sf::Clock clock;

    while (window.isOpen()) {
        window.handleEvents(onClose);
        window.clear();

        game.run(clock, window);
        game.update(window);

        window.display();
    }
}
