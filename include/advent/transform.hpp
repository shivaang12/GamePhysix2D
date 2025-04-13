#ifndef ADVENT_TRANSFORM_HPP
#define ADVENT_TRANSFORM_HPP

#include <SFML/Graphics.hpp>

namespace advent {

struct Transform2D {
    float x_;
    float y_;
    float cos_;
    float sin_;
    Transform2D(const float& x, const float& y, const float& angle);
    Transform2D(const sf::Vector2f& position, const float& angle);
};

}  // namespace advent

#endif  // ADVENT_TRANSFORM_HPP
