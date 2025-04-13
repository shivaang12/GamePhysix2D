#include "advent/transform.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>

namespace advent {

Transform2D::Transform2D(const float& x, const float& y, const float& angle)
    : x_(x), y_(y), cos_(std::cos(angle)), sin_(std::sin(angle)) {}

Transform2D::Transform2D(const sf::Vector2f& position, const float& angle)
    : x_(position.x), y_(position.y), cos_(std::cos(angle)), sin_(std::sin(angle)) {}

}  // namespace advent
