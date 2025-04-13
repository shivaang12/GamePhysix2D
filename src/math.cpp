#include <SFML/Graphics.hpp>

#include "advent/math.hpp"

namespace advent {

sf::Vector2f math::transform(const sf::Vector2f& pos,
                             const Transform2D& trans) {
    const auto rx = pos.x * trans.cos_ - pos.y * trans.sin_;
    const auto ry = pos.x * trans.sin_ + pos.y * trans.cos_;

    return sf::Vector2f({rx + trans.x_, ry + trans.y_});
}

float math::dotProduct(const sf::Vector2f& vecA, const sf::Vector2f& vecB) {
    return vecA.x * vecB.x + vecB.y * vecA.y;
}

float math::calculateLengthOfVector(const sf::Vector2f& vec) {
    float temp = std::sqrt(dotProduct(vec, vec));
    return temp;
}

sf::Vector2f math::calculateUnitVector(const sf::Vector2f& vec) {
    const auto length = calculateLengthOfVector(vec);

    // Check for Numerical Stability
    if (length < 0.0001f) {
        return sf::Vector2f({vec.x, vec.y});
    }
    return sf::Vector2f({vec.x / length, vec.y / length});
}

}  // namespace advent
