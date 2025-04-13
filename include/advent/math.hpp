#ifndef ADVENT_MATH_HPP
#define ADVENT_MATH_HPP

#include <SFML/Graphics.hpp>

#include "advent/transform.hpp"

namespace advent {

namespace math {

sf::Vector2f transform(const sf::Vector2f &pos, const Transform2D &trans);
float dotProduct(const sf::Vector2f &vecA, const sf::Vector2f &vecB);
float calculateLengthOfVector(const sf::Vector2f &vec);
sf::Vector2f calculateUnitVector(const sf::Vector2f &vec);
sf::Vector2f getTransformedMidPoint(const std::vector<sf::Vector2f> &vert);

}

}

#endif // ADVENT_MATH_HPP
