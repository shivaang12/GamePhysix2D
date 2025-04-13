#ifndef ADVENT_BODY_HPP
#define ADVENT_BODY_HPP

#include <array>

#include <SFML/Graphics.hpp>

namespace advent {
class BoxBody {
   public:
    BoxBody(float x, float y, float rotation_, float height_, float width, sf::Color color, bool is_static=false);
    BoxBody() = default;

    // Setter and Getter methods
    const sf::Vector2f& getPosition() const;
    float getRotation() const;
    float getWidth() const;
    float getHeight() const;
    bool isStatic() const;
    const sf::Vector2f& getLinearVelocity() const;
    void setLinearVelocity(const sf::Vector2f& velocity);
    float getRestitution() const;
    float getInvMass() const;
    void setTouchGround();
    void resetTouchGround();
    bool getTouchGround() const;

    // Methods for Transformation
    void move(const sf::Vector2f &pos);
    void moveTo(const sf::Vector2f &pos);

    void rotate(const float &angle);
    void rotateTo(const float &angle);

    // 
    void updateVertices();
    const std::array<sf::Vector2f, 4>& getTVertices() const;

    //
    const sf::RectangleShape& readShape() const;

    // Similation
    void addForce(const sf::Vector2f& force);
    void step(float time, const sf::Vector2f& gravity, size_t iter);


   private:
    // Physical Attributes
    sf::Vector2f position_;
    float rotation_;
    float height_;
    float width_;
    sf::Vector2f linear_velocity_;
    sf::Vector2f force_;
    float inv_mass_;
    float restitution_;

    // Collision Attributes
    std::array<sf::Vector2f, 4> primitive_vertices_;
    std::array<sf::Vector2f, 4> transformed_vertices_;

    // Drawing object
    sf::RectangleShape d_shape_;

    // Misc
    bool update_required_;
    bool static_;
    bool touch_ground_;
};
}  // namespace advent

#endif  // ADVENT_BODY_HPP