#ifndef ADVENT_DEBUG_HPP
#define ADVENT_DEBUG_HPP

#include <array>

#include <SFML/Graphics.hpp>

namespace advent {
namespace debug {
const int GLOBAL_PADDING = 20;

constexpr sf::Color GROUND_COLOR(70, 63, 58);

const std::array<sf::Color, 7> VALID_COLORS = {
    sf::Color(52, 82, 74),  sf::Color(162, 232, 221), sf::Color(184, 12, 9),
    sf::Color(107, 43, 6),  sf::Color(229, 231, 230), sf::Color(160, 113, 120),
    sf::Color(119, 98, 116)};

int getRandInt(const int &low, const int &high);
float getRandFloat(const float &low, const float &high);

}
}  // namespace advent

#endif  // ADVENT_DEBUG_HPP