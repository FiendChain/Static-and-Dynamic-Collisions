#include "App.hpp"

#include <imgui-sfml/imgui-SFML.h>

void App::PollEvents()
{
    sf::Event event;
    while (m_Window.pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);
        if (event.type == sf::Event::Closed)
        {
            m_Window.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            switch (event.key.code)
            {
            case sf::Mouse::Left:
                SelectBall();
                break;
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased)
        {
            switch (event.key.code)
            {
            case sf::Mouse::Left:
                m_DragCurrentBall = false;
                break;
            }
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {

            }
        }
    }
}