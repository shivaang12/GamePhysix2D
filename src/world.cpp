#include <array>
#include <cmath>
#include <iostream>
#include <limits>

#include "advent/debug.hpp"
#include "advent/math.hpp"
#include "advent/world.hpp"

namespace advent {

World::World(const float& player_x,
             const float& player_y,
             const float& width,
             const float& height)
    : gravity_({0.f, 9.81f * 40.f}),
      s_level_(""),
      level_width_(0),
      level_height_(0),
      level_block_size_(0) {

    this->level_width_ = 20;
    this->level_height_ = 15;
    this->level_block_size_ = 64;

    this->s_level_ += "....................";
    this->s_level_ += "....................";
    this->s_level_ += ".######.............";
    this->s_level_ += ".....###............";
    this->s_level_ += "......###...........";
    this->s_level_ += ".......###..........";
    this->s_level_ += "........###...##....";
    this->s_level_ += "...............#....";
    this->s_level_ += "...........##..#....";
    this->s_level_ += "..........##..##....";
    this->s_level_ += ".........##..###....";
    this->s_level_ += ".......####.........";
    this->s_level_ += "..........######....";
    this->s_level_ += "####################";
    this->s_level_ += "####################";

    this->body_list_.reserve((this->level_width_ * this->level_height_)+1);

    int half_level_block_size = this->level_block_size_ / 2;

    this->body_list_.emplace_back(
        BoxBody((float)0 * this->level_block_size_ + half_level_block_size,
                (float)11 * this->level_block_size_ + half_level_block_size,
                0.f,
                (float)this->level_block_size_,
                (float)this->level_block_size_,
                debug::VALID_COLORS[2]));

    for (int j = 0; j < this->level_height_; j++) {
        for (int i = 0; i < this->level_width_; i++) {

            if (this->s_level_[(j * this->level_width_) + i] == '#') {

                this->body_list_.emplace_back(BoxBody(
                    (float)i * this->level_block_size_ + half_level_block_size,
                    (float)j * this->level_block_size_ + half_level_block_size,
                    0.f,
                    (float)this->level_block_size_,
                    (float)this->level_block_size_,
                    debug::GROUND_COLOR,
                    true));
            }
        }
    }
}

void World::addBody(const sf::Vector2i& position) {
    float rand_x = (float)position.x;
    float rand_y = (float)position.y;

    float radius = debug::getRandFloat(30, 50);
    const int color_idx = debug::getRandInt(0, debug::VALID_COLORS.size());

    this->body_list_.emplace_back(BoxBody(
        rand_x, rand_y, 0.f, radius, radius, debug::VALID_COLORS[color_idx]));
}

void World::removeBody(const size_t index) {
    if (index > this->body_list_.size() - 1) {
        this->body_list_.erase(this->body_list_.begin() + index);
    }
}

BoxBody* World::exposeBodyAtIndx(size_t index) {
    return &this->body_list_[index];
}

const std::vector<advent::BoxBody>& World::readBodyList() const {
    return this->body_list_;
}

void World::handleCollision() {
    for (int i = 0; i < this->body_list_.size(); i++) {

        body_list_[i].updateVertices();

        for (int j = 0; j < this->body_list_.size(); j++) {

            // Obvious Check
            if (i == j) {
                continue;
            }

            body_list_[j].updateVertices();

            if (body_list_[i].isStatic() && body_list_[j].isStatic()) {
                continue;
            }

            // Check if Collision
            sf::Vector2f normal_of_collision({0.f, 0.f});
            float depth_of_collision = 0.f;

            if (this->intersectPolygons(body_list_[i].getTVertices(),
                                        body_list_[j].getTVertices(),
                                        body_list_[i].getPosition(),
                                        body_list_[j].getPosition(),
                                        normal_of_collision,
                                        depth_of_collision)) {

                // std::cout << "[COLLISION]" << "\n";

                if (body_list_[i].isStatic()) {
                    body_list_[j].move(normal_of_collision *
                                       (depth_of_collision * 1.0f));

                    float check_1 = math::dotProduct(normal_of_collision,
                                                     sf::Vector2f({0.f, 1.f}));
                    // std::cout << check_1 << "\n";
                    if (std::abs(check_1) < 1.01f &&
                        std::abs(check_1) > 0.97f) {
                        sf::Vector2f current_vel =
                            body_list_[j].getLinearVelocity();
                        if (current_vel.y >= 0.f) {
                            body_list_[j].setTouchGround();
                            current_vel.y = 0.f;
                            body_list_[j].setLinearVelocity(current_vel);
                        }
                    }

                } else if (body_list_[j].isStatic()) {
                    body_list_[i].move(normal_of_collision *
                                       (depth_of_collision * -1.0f));

                    float check_1 = math::dotProduct(normal_of_collision,
                                                     sf::Vector2f({0.f, 1.f}));

                    if (std::abs(check_1) < 1.01f &&
                        std::abs(check_1) > 0.97f) {
                        sf::Vector2f current_vel =
                            body_list_[i].getLinearVelocity();
                        if (current_vel.y >= 0.f) {
                            body_list_[i].setTouchGround();
                            current_vel.y = 0.f;
                            body_list_[i].setLinearVelocity(current_vel);
                        }
                    }

                } else {
                    body_list_[i].move(normal_of_collision *
                                       (depth_of_collision / 2.0f) * -1.0f);
                    body_list_[j].move(normal_of_collision *
                                       (depth_of_collision / 2.0f) * 1.0f);
                }

                body_list_[i].updateVertices();
                body_list_[j].updateVertices();

                this->resolveCollision(body_list_[i],
                                       body_list_[j],
                                       normal_of_collision,
                                       depth_of_collision);
            }
        }
    }
}

bool World::intersectPolygons(const std::array<sf::Vector2f, 4>& tf_vertices_A,
                              const std::array<sf::Vector2f, 4>& tf_vertices_B,
                              const sf::Vector2f& center_A,
                              const sf::Vector2f& center_B,
                              sf::Vector2f& normal_of_collision,
                              float& depth_of_collision) const {

    sf::Vector2f normal = sf::Vector2f({0.f, 0.f});
    float depth = std::numeric_limits<float>::max();

    for (int i = 0; i < tf_vertices_A.size(); i++) {
        const auto& tf_vert_1 = tf_vertices_A[i];
        const auto& tf_vert_2 =
            tf_vertices_A[(i + 1) %
                          tf_vertices_A.size()];  // To make it circular

        const auto& tf_vert_diff = tf_vert_2 - tf_vert_1;
        const auto& normal_of_1_n_2 =
            sf::Vector2f({-tf_vert_diff.y, tf_vert_diff.x});

        float minA = std::numeric_limits<float>::max();
        float minB = std::numeric_limits<float>::max();
        float maxA = -std::numeric_limits<float>::max();
        float maxB = -std::numeric_limits<float>::max();

        projectVertices(tf_vertices_A, normal_of_1_n_2, minA, maxA);
        projectVertices(tf_vertices_B, normal_of_1_n_2, minB, maxB);

        if (minA >= maxB || minB >= maxA) {
            // There is seperation
            return false;
        }

        float axis_depth = std::min(maxB - minA, maxA - minB);

        if (axis_depth < depth) {
            depth = axis_depth;
            normal = normal_of_1_n_2;
        }
    }

    for (int i = 0; i < tf_vertices_B.size(); i++) {
        const auto& tf_vert_1 = tf_vertices_B[i];
        const auto& tf_vert_2 =
            tf_vertices_B[(i + 1) %
                          tf_vertices_B.size()];  // To make it circular

        const auto& tf_vert_diff = tf_vert_2 - tf_vert_1;
        const auto& normal_of_1_n_2 =
            sf::Vector2f({-tf_vert_diff.y, tf_vert_diff.x});

        float minA = std::numeric_limits<float>::max();
        float minB = std::numeric_limits<float>::max();
        float maxA = -std::numeric_limits<float>::max();
        float maxB = -std::numeric_limits<float>::max();

        projectVertices(tf_vertices_A, normal_of_1_n_2, minA, maxA);
        projectVertices(tf_vertices_B, normal_of_1_n_2, minB, maxB);

        if (minA >= maxB || minB >= maxA) {
            // There is seperation
            return false;
        }

        float axis_depth = std::min(maxB - minA, maxA - minB);

        if (axis_depth < depth) {
            depth = axis_depth;
            normal = normal_of_1_n_2;
        }
    }

    // Out Variables
    const auto normal_magnitude = math::calculateLengthOfVector(normal);
    const auto direction_B_A = center_B - center_A;
    normal_of_collision = normal / normal_magnitude;

    if (math::dotProduct(direction_B_A, normal_of_collision) < 0.f) {
        normal_of_collision = -normal_of_collision;
    }

    depth_of_collision = depth / normal_magnitude;

    return true;
}

void World::projectVertices(const std::array<sf::Vector2f, 4>& tf_vertices,
                            const sf::Vector2f& normal_axis,
                            float& min,
                            float& max) const {

    for (int i = 0; i < tf_vertices.size(); i++) {
        float proj = math::dotProduct(tf_vertices[i], normal_axis);

        if (proj < min) {
            min = proj;
        }
        if (proj > max) {
            max = proj;
        }
    }

    return;
}

void World::resolveCollision(BoxBody& body_A,
                             BoxBody& body_B,
                             const sf::Vector2f& normal,
                             const float& depth) {

    const sf::Vector2f relativeVelocity =
        body_B.getLinearVelocity() - body_A.getLinearVelocity();

    const float dot_ = math::dotProduct(relativeVelocity, normal);

    if (dot_ > 0.f) {
        return;
    }

    float e = 0.01f;

    float j = -(1.f + e) * dot_;
    // std::cout << j << " ";
    j /= (body_A.getInvMass()) + (body_B.getInvMass());

    const sf::Vector2f d_body_A_lv = (j * body_A.getInvMass()) * normal;
    const sf::Vector2f d_body_B_lv = (j * body_B.getInvMass()) * normal;

    body_A.setLinearVelocity(body_A.getLinearVelocity() - d_body_A_lv);
    body_B.setLinearVelocity(body_B.getLinearVelocity() + d_body_B_lv);
}

void World::step(float time) {
    // Movement
    size_t iter = 30;
    for (size_t j = 0; j < iter; j++) {
        for (size_t i = 0; i < this->body_list_.size(); i++) {
            this->body_list_[i].step(time, this->gravity_, iter);
        }

        // Collision
        this->handleCollision();
    }
}

}  // namespace advent
