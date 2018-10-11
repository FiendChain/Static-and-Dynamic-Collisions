#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <random>
#include <vector>
#include "Ball.hpp"

class App
{
    private:
        sf::RenderWindow m_Window;
        const unsigned int m_Width, m_Height, m_Fps;
        sf::Clock m_Clock;
        sf::Mutex m_Mutex;
        std::mt19937 m_RngEngine;
        std::vector<std::shared_ptr<Ball>> m_Balls;
        std::shared_ptr<Ball> m_CurrentBall; // current ball
        bool m_DragCurrentBall;
        sf::RectangleShape m_CurrentBallOutline;
        bool m_EnableGravity, m_EnableDrag; // flags
    public:
        App(unsigned int width, unsigned int height, unsigned int fps);
        ~App();
        void Run();
    private:
        void PollEvents();
        void Render();
        void RenderImGui();
        void Update();
        // balls
        void SelectBall();
        void RandomiseBalls();
        void UpdateBalls();
        bool DragCurrentBall();
};