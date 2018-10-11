#include "Ball.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>

Ball::Ball(float mass, float radius)
    : m_Mass(mass), m_Velocity(0, 0), m_Acceleration(0, 0)
{
    setFillColor(sf::Color::White);
    setRadius(radius);
    setOrigin(sf::Vector2f(radius, radius));
    setPosition(0, 0);
}

void Ball::Update(float deltaTime)
{
    m_Velocity += m_Acceleration * deltaTime;
    setPosition(getPosition() + m_Velocity*deltaTime);
    m_Acceleration.x = m_Acceleration.y = 0;
}

void Ball::ApplyForce(float x, float y)
{
    m_Acceleration.x += x / m_Mass; // f = ma, a = f/m
    m_Acceleration.y += y / m_Mass;
}

void Ball::ApplyForce(const sf::Vector2f& force)
{
    m_Acceleration += force / m_Mass;
}

bool Ball::ApplyCollision(Ball& ball)
{
    // get collision
    sf::Vector2f posDiff = getPosition() - ball.getPosition();
    float distanceSquared = posDiff.x*posDiff.x + posDiff.y*posDiff.y;
    float distance = pow(distanceSquared, 0.5f);
    float overlap = distance - (getRadius() + ball.getRadius());
    if (overlap > 0) return false;
    // apply dynamic collision
    sf::Vector2f velDiff = GetVelocity() - ball.GetVelocity();
    sf::Vector2f velNormal = ((velDiff.x*posDiff.x + velDiff.y*posDiff.y)/distanceSquared)*posDiff;
    float velNormalSquared = velNormal.x*velNormal.x + velNormal.y*velNormal.y;
    float velNormalAbs = pow(velNormalSquared, 0.5f);
    float m1 = GetMass(), m2 = ball.GetMass();
    float v1 = ((m1-m2)/(m1+m2))*velNormalAbs;
    float v2 = (m1/m2)*(velNormalAbs-v1);
    sf::Vector2f velNormalUnit = velNormal/velNormalAbs;
    SetVelocity(velNormalUnit*v1);
    ball.SetVelocity(velNormalUnit*v2);
    // apply static collision
    sf::Vector2f displacement = posDiff * (-overlap/distance);
    setPosition(getPosition()+displacement);
    ball.setPosition(ball.getPosition()-displacement);
    return true;
}

void Ball::SetVelocity(float x, float y)
{
    m_Velocity.x = x;
    m_Velocity.y = y;
}

void Ball::SetVelocity(sf::Vector2f velocity)
{
    m_Velocity = velocity;
}

void Ball::ApplyAcceleration(float x, float y)
{
    m_Acceleration.x += x;
    m_Acceleration.y += y;
}

void Ball::ApplyAcceleration(sf::Vector2f acceleration)
{
    m_Acceleration += acceleration;
}

