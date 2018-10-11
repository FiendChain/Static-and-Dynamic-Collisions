#include "App.hpp"
#include <SFML/Graphics.hpp>

void App::UpdateBalls()
{
    static float deltaTime = 1.0f/m_Fps;
    static sf::Vector2f accelerationGravity = sf::Vector2f(0, 9.8)*(float)m_Fps;
    for (auto& ballA: m_Balls)
    {
        for (auto& ballB: m_Balls)
        {
            if (ballA != ballB)
            {
                ballA->ApplyCollision(*ballB);
            }
        }
    }
    for (auto& ball: m_Balls)
    {
        // gravity
        if (m_EnableGravity) ball->ApplyAcceleration(accelerationGravity);
        // drag
        if (m_EnableDrag) ball->SetVelocity(ball->GetVelocity()*0.98f); 
        // collision boxes
        sf::Vector2f ballPos = ball->getPosition();
        sf::Vector2f ballVel = ball->GetVelocity();
        float radius = ball->getRadius();
        if (ballPos.x < radius) 
        {
            ballPos.x = radius;
            ballVel.x = ballVel.x < 0 ? -ballVel.x: ballVel.x;
        }
        else if (ballPos.x > m_Width-radius) 
        {
            ballPos.x = m_Width-radius;
            ballVel.x = ballVel.x > 0 ? -ballVel.x: ballVel.x;
        }
        if (ballPos.y < radius) {
            ballPos.y = radius;
            ballVel.y = ballVel.y < 0 ? -ballVel.y: ballVel.y;
        }
        else if (ballPos.y > m_Height-radius) 
        {
            ballPos.y = m_Height-radius;
            ballVel.y = ballVel.y > 0 ? -ballVel.y: ballVel.y;
        }
        ball->setPosition(ballPos);
        ball->SetVelocity(ballVel);
        // update
        ball->Update(deltaTime);
    }
}

void App::SelectBall()
{
    auto mousePos = sf::Mouse::getPosition(m_Window);
    sf::Vector2f clickPos(mousePos.x, mousePos.y);
    for (auto& ball: m_Balls)
    {
        sf::Vector2f diff = ball->getPosition()-clickPos;
        float distanceSquared = diff.x*diff.x + diff.y*diff.y;
        if (distanceSquared < ball->getRadius()*ball->getRadius()) 
        {
            if (m_CurrentBall == ball)
            {
                m_DragCurrentBall = true;
            }
            else if (m_CurrentBall != ball)
            {
                m_CurrentBall = ball;
                m_DragCurrentBall = true;
                sf::Vector2f origin = sf::Vector2f(ball->getRadius(), ball->getRadius())*1.1f;
                m_CurrentBallOutline.setSize(origin*2.0f);
                m_CurrentBallOutline.setOrigin(origin);
            }
            return;
        }
    }
    m_CurrentBall = nullptr;
    m_DragCurrentBall = false;
}

void App::RandomiseBalls()
{
    std::uniform_real_distribution<float> 
        radius(20, 30), mass(1, 10),
        posX(0, m_Width), posY(0, m_Height),
        velX(-10, 10), velY(-10, 10);

    for (auto& ball: m_Balls)
    {
        ball = std::make_shared<Ball>(mass(m_RngEngine), radius(m_RngEngine));
        ball->setPosition(posX(m_RngEngine), posY(m_RngEngine));
        ball->SetVelocity(velX(m_RngEngine), velY(m_RngEngine));
        ball->setFillColor(sf::Color::Transparent);
        ball->setOutlineColor(sf::Color::Black);
        ball->setOutlineThickness(2.0f);
    }
}

bool App::DragCurrentBall()
{
    if (!m_CurrentBall || !m_DragCurrentBall) return false;
    auto mousePos = sf::Mouse::getPosition(m_Window);
    sf::Vector2f diff = sf::Vector2f(mousePos.x, mousePos.y) - m_CurrentBall->getPosition();
    m_CurrentBall->SetVelocity(diff*(float)m_Fps);
    return true;
}