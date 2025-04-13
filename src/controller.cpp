#include <SFML/Graphics.hpp>
#include <iostream>

#include "advent/controller.hpp"
#include "advent/math.hpp"

namespace advent {

Controller::Controller(BoxBody* player, float speed)
    : player_(player), speed_(speed) {}

void Controller::movePlayerUsingInput(float time) const {
    
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space) && this->player_->getTouchGround()) {
            sf::Vector2f current_vel = this->player_->getLinearVelocity();
            current_vel.y = 0.f; // reset y axis
            this->player_->setLinearVelocity(current_vel + sf::Vector2f({ 0.f, -340.f }));
            this->player_->resetTouchGround();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right)) {
            if (this->player_->getTouchGround()) {
                this->player_->move(sf::Vector2f({ 1.f, 0.f }) * this->speed_ * time);
            } else {
                this->player_->move(sf::Vector2f({ 1.f, 0.f }) * this->speed_ * 0.7f * time);
            }
            this->player_->resetTouchGround();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left)) {
            if (this->player_->getTouchGround()) {
                this->player_->move(sf::Vector2f({ -1.f, 0.f }) * this->speed_ * time);
            } else {
                this->player_->move(sf::Vector2f({ -1.f, 0.f }) * this->speed_ * 0.7f * time);
            }
            this->player_->resetTouchGround();
        }
    }

}  // namespace advent
