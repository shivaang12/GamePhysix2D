#ifndef ADVENT_WORLD_HPP
#define ADVENT_WORLD_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include "advent/body.hpp"

namespace advent {

class World {

   public:
    World(const float& player_x, const float& player_y, const float& width,
          const float& height);
    World() = default;

    // Collision
    void handleCollision();
    void resolveCollision(BoxBody& body_A, BoxBody& body_B, const sf::Vector2f& normal, const float& depth);

    // Body Manipulation
    void addBody(const sf::Vector2i& Position);
    void removeBody(const size_t index);

    // Expose Methods
    BoxBody* exposeBodyAtIndx(size_t index);
    const std::vector<advent::BoxBody>& readBodyList() const;

    // Simulation
    void step(float time);

   private:
    std::vector<advent::BoxBody> body_list_;
    sf::Vector2f gravity_;

    // Level
    std::string s_level_;
    int level_width_;
    int level_height_;
    int level_block_size_;

    // Collision Helper Methods
    bool intersectPolygons(const std::array<sf::Vector2f, 4>& tf_vertices_A,
                           const std::array<sf::Vector2f, 4>& tf_vertices_B,
                           const sf::Vector2f& center_A,
                           const sf::Vector2f& center_B,
                           sf::Vector2f& normal_of_collision,
                           float& depth_of_collision) const;
    void projectVertices(const std::array<sf::Vector2f, 4>& tf_vertices,
                         const sf::Vector2f& normal_axis, float& min,
                         float& max) const;
};

}  // namespace advent

#endif // ADVENT_WORLD_HPP
