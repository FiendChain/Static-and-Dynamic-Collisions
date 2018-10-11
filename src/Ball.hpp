#pragma once
#include <SFML/Graphics.hpp>

class Ball: public sf::CircleShape
{
    private:
        float m_Mass;
        sf::Vector2f m_Velocity;
        sf::Vector2f m_Acceleration;
    public:
        Ball(float mass, float radius);
        void Update(float deltaTime);
        void ApplyForce(float x, float y);
        void ApplyForce(const sf::Vector2f& force);
        void ApplyAcceleration(float x, float y);
        void ApplyAcceleration(sf::Vector2f acceleration);
        bool ApplyCollision(Ball &ball);
        inline const float GetMass() const { return m_Mass; }
        inline const sf::Vector2f& GetVelocity() const { return m_Velocity; }
        void SetVelocity(float x, float y);
        void SetVelocity(sf::Vector2f velocity);
};