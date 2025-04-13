#include "advent/game.hpp"
#include "advent/world.hpp"
#include "advent/controller.hpp"

#include <iostream>
#include <chrono>
#include <string>

namespace advent
{

void Game::initialize() {
    this->duration_ = 0.0;

    if (!this->font_.openFromFile("/Users/shivangpatel/projects/advent_0.0.1/Ubuntu-R.ttf")) {
        std::cout << "FONT NOT FOUND\n";
        exit(0);
    }

    this->world_ = World(1000.f, 500.f, 50.f, 100.f);
    // std::cout << "[EXPOSE] " << this->world_.exposeBodyAtIndx(0) << "\n";
    this->player_controller_ = Controller(this->world_.exposeBodyAtIndx(0), 200.f);
    // std::cout << "[EXPOSE] " << this->world_.exposeBodyAtIndx(1) << "\n";

}

void Game::run(sf::Clock& clock, sf::Window& window) {

    float time = clock.restart().asSeconds();
    this->player_controller_.movePlayerUsingInput(time);
    auto start = std::chrono::high_resolution_clock::now();
    this->world_.step(time);
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate duration
    std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    this->duration_ = duration.count();

}

void Game::update(sf::RenderWindow& window) {
    const auto body_list = this->world_.readBodyList();

    for (const auto &shape_var : body_list) {
        window.draw(shape_var.readShape());
    }

    sf::Text text(this->font_);
    std::string to_display = "Step : " + std::to_string(this->duration_) + "\n Total Objects " + std::to_string(this->world_.readBodyList().size());
    text.setString(to_display);
    text.setCharacterSize(32);

    window.draw(text);

}

} // namespace advent

