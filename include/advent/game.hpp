#ifndef ADVENT_GAME_HPP
#define ADVENT_GAME_HPP

#include <SFML/Graphics.hpp>

#include "advent/controller.hpp"
#include "advent/world.hpp"

namespace advent {

class Game {

   public:
    Game() = default;
    void initialize();
    void run(sf::Clock& clock, sf::Window& window);
    void update(sf::RenderWindow& window);

   private:
    World world_;
    Controller player_controller_;
    sf::Font font_;
    double duration_;
};

}  // namespace advent

#endif  // ADVENT_GAME_HPP
