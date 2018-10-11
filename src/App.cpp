#include "App.hpp"
#include "Ball.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <random>
#include <time.h>
#include <functional>

#include <imgui-sfml/imgui-SFML.h>

App::App(unsigned int width, unsigned int height, unsigned int fps)
    : m_Width(width), m_Height(height), m_Fps(fps), 
      m_Window(sf::VideoMode(width, height), "Static and dynamic collisions"),
      m_RngEngine(time(NULL)),
      m_Balls(10), 
      m_CurrentBall(nullptr), m_DragCurrentBall(false), 
      m_EnableGravity(true), m_EnableDrag(true)
{
    m_Window.setFramerateLimit(m_Fps);
    ImGui::SFML::Init(m_Window);
    RandomiseBalls();
    m_CurrentBallOutline.setFillColor(sf::Color::Transparent);
    m_CurrentBallOutline.setOutlineColor(sf::Color::Green);
    m_CurrentBallOutline.setOutlineThickness(1.0f);
}

App::~App()
{

}

void App::Run()
{
    sf::Thread updateThread(std::bind(&Update, this));
    updateThread.launch();

    sf::Time lastUpdate = m_Clock.getElapsedTime();
    int tickRate = 1000/(float)m_Fps;
    while (m_Window.isOpen())
    {
        if ((m_Clock.getElapsedTime()-lastUpdate).asMilliseconds() > tickRate)
        {
            lastUpdate = m_Clock.getElapsedTime();
            m_Mutex.lock();
            Render();
            PollEvents();
            m_Mutex.unlock();
        }
    }
}

void App::Update()
{
    sf::Time lastUpdate = m_Clock.getElapsedTime();
    int tickRate = 1000/(float)m_Fps;
    while (m_Window.isOpen())
    {
        if ((m_Clock.getElapsedTime()-lastUpdate).asMilliseconds() > tickRate)
        {
            lastUpdate = m_Clock.getElapsedTime();
            m_Mutex.lock();
            DragCurrentBall();
            UpdateBalls();
            if (m_CurrentBall) m_CurrentBallOutline.setPosition(m_CurrentBall->getPosition());
            m_Mutex.unlock();
        }
    }
}

