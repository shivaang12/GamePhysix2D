#include <array>
#include <random>

#include <SFML/Graphics.hpp>

#include "advent/debug.hpp"

namespace advent {

int debug::getRandInt(const int& low, const int& high) {
    return (int)debug::getRandFloat((float)low, (float)high);
}

float debug::getRandFloat(const float& low, const float& high) {
    // Create a random device (for non-deterministic seeding)
    std::random_device rd;

    // Use Mersenne Twister engine
    std::mt19937 gen(rd());

    // Define a uniform real distribution between 0.0 and 1.0
    std::uniform_real_distribution<float> dist(low, high);

    return dist(gen);
}

}  // namespace advent
