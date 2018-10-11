#include "App.hpp"
#include <SFML/Graphics.hpp>

#include <imgui/imgui.h>
#include <imgui-sfml/imgui-SFML.h>

void App::Render()
{
    // window
    m_Window.clear(sf::Color::White);
    // balls
    for (auto& ball: m_Balls)
    {
        m_Window.draw(*ball);
    }
    if (m_CurrentBall) m_Window.draw(m_CurrentBallOutline);
    RenderImGui();
    ImGui::SFML::Render(m_Window);
    m_Window.display();
}

void App::RenderImGui()
{
    static sf::Clock imguiClock;
    ImGui::SFML::Update(m_Window, imguiClock.restart());
    ImGui::Begin("Info");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::Checkbox("Enable gravity", &m_EnableGravity);
    ImGui::Checkbox("Enable drag", &m_EnableDrag);
    if (m_CurrentBall)
    {
        ImGui::Begin("Current Ball");
        ImGui::Text("Mass: %.2f", m_CurrentBall->GetMass());
        ImGui::Text("Radius: %.2f", m_CurrentBall->getRadius());
        ImGui::Text("Position: %.2f, %.2f", m_CurrentBall->getPosition().x, m_CurrentBall->getPosition().y);
        ImGui::Text("Velocity: %.2f, %.2f", m_CurrentBall->GetVelocity().x, m_CurrentBall->GetVelocity().y);
        ImGui::End();
    }
    ImGui::End();
}
