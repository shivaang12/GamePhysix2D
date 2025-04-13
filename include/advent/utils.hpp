#ifndef ADVENT_UTILS_HPP
#define ADVENT_UTILS_HPP

#include <SFML/Graphics.hpp>

#include "advent/transform.hpp"

// Some serious missing op overloading
namespace sf {
Vector2f operator-(const Vector2f& v, const float& scalar_float) {
    return Vector2f({v.x - scalar_float, v.y - scalar_float});
}

Vector2f operator+(const Vector2f& v, const float& scalar_float) {
    return Vector2f({v.x + scalar_float, v.y + scalar_float});
}

Vector2f operator/(const Vector2f& v, const float& scalar_float) {
    return Vector2f({v.x / scalar_float, v.y / scalar_float});
}
}  // namespace sf

#endif  // ADVENT_UTILS_HPP