#include "advent/body.hpp"
#include <SFML/Graphics.hpp>
#include "advent/math.hpp"
#include "advent/transform.hpp"
#include <iostream>

namespace advent {

BoxBody::BoxBody(float x, float y, float rotation, float width, float height,
                 sf::Color color, bool is_static)
    : position_(x, y),
      rotation_(rotation),
      width_(width),
      height_(height),
      static_(is_static),
      linear_velocity_({0.f, 0.f}),
      force_({0.f, 0.f}),
      inv_mass_(1.f/50.f),
      restitution_(1.0f),
      touch_ground_(false) {

    // Initialize Vertices
    float left = -(this->width_ / 2.f);
    float right = left + this->width_;
    float top = -(this->height_ / 2.f);
    float bottom = top + this->height_;

    this->primitive_vertices_ = {
        sf::Vector2f({left, top}), sf::Vector2f({right, top}),
        sf::Vector2f({right, bottom}), sf::Vector2f({left, bottom})};

    this->transformed_vertices_ = {
        sf::Vector2f({left, top}), sf::Vector2f({right, top}),
        sf::Vector2f({right, bottom}), sf::Vector2f({left, bottom})};

    // Initialize Drawing Object for SFML
    this->d_shape_ = sf::RectangleShape({this->width_, this->height_});
    this->d_shape_.setOrigin({this->width_ / 2.f, this->height_ / 2.f});
    this->d_shape_.setFillColor(color);

    // Setting this false since we already updated the position
    this->update_required_ = true;

    this->updateVertices();

    //
    if (this->static_) {
        this->inv_mass_ = 0.f;
    }
}

void BoxBody::updateVertices() {
    if (this->update_required_) {
        this->d_shape_.setPosition(this->position_);
        this->d_shape_.setRotation(sf::radians(this->rotation_));

        // Update vertices
        const auto current_transform =
            Transform2D(this->position_, this->rotation_);

        std::array<sf::Vector2f, 4> new_transform;

        for (int i = 0; i < 4; i++) {
            new_transform[i] = math::transform(this->primitive_vertices_[i],
                                               current_transform);
        }

        this->transformed_vertices_ = new_transform;

        this->update_required_ = false;
    }
}

const sf::Vector2f& BoxBody::getPosition() const {
    return this->position_;
}

float BoxBody::getRotation() const {
    return this->rotation_;
}

float BoxBody::getWidth() const {
    return this->width_;
}

float BoxBody::getHeight() const {
    return this->height_;
}

bool BoxBody::isStatic() const {
    return this->static_;
}

const sf::Vector2f& BoxBody::getLinearVelocity() const {
    return this->linear_velocity_;
}

void BoxBody::setLinearVelocity(const sf::Vector2f& velocity) {
    // if(!this->static_) {
    //     this->linear_velocity_ = velocity;
    // }
    this->linear_velocity_ = velocity;
}

float BoxBody::getRestitution() const {
    return this->restitution_;
}

float BoxBody::getInvMass() const {
    return this->inv_mass_;
}

void BoxBody::setTouchGround() {
    this->touch_ground_ = true;
}

void BoxBody::resetTouchGround() {
    this->touch_ground_ = false;
}

bool BoxBody::getTouchGround() const {
    return this->touch_ground_;
}

void BoxBody::move(const sf::Vector2f& pos) {
    this->position_ += pos;
    this->update_required_ = true;
}

void BoxBody::moveTo(const sf::Vector2f& pos) {
    this->position_ = pos;
    this->update_required_ = true;
}

void BoxBody::rotate(const float& angle) {
    this->rotation_ += angle;
    this->update_required_ = true;
}

void BoxBody::rotateTo(const float& angle) {
    this->rotation_ = angle;
    this->update_required_ = true;
}

const std::array<sf::Vector2f, 4>& BoxBody::getTVertices() const {
    return this->transformed_vertices_;
}

const sf::RectangleShape& BoxBody::readShape() const {
    return this->d_shape_;
}

void BoxBody::addForce(const sf::Vector2f& force) {
    this->force_ += force;
}

void BoxBody::step(float time, const sf::Vector2f& gravity, size_t iter) {
    if(this->static_) {
        return;
    }

    sf::Vector2f gravity_local({0.f, 0.f});
    gravity_local = gravity;

    if(this->touch_ground_) {
        this->d_shape_.setFillColor(sf::Color(119, 98, 116));
        // this->linear_velocity_.y = 0.f;
    } else {
        this->d_shape_.setFillColor(sf::Color(160, 113, 120));
        // gravity_local = gravity;
    }
    // const auto acceleration = this->force_ * this->inv_mass_;

    // this->linear_velocity_ += acceleration * time;
    time = time/ (float)iter;

    // std::cout << this->force_.x << " " << this->force_.y << "\n";

    // this->linear_velocity_ += this->force_ * time;
    this->linear_velocity_ += gravity_local * time;

    this->position_ += this->linear_velocity_ * time;
    this->update_required_ = true;

    this->force_ = {0.f, 0.f};

    return;
}

}  // namespace advent
