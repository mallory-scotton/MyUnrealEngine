///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "Utils/Types.hpp"
#include "GraphEditor/UClass.hpp"
#include "GraphEditor/Nodes/ArithmeticNodes.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui-SFML.h>
#include <imgui_node_editor.h>
#include <widgets.h>

///////////////////////////////////////////////////////////////////////////////
namespace en = ax::NodeEditor;

///////////////////////////////////////////////////////////////////////////////
int main(void)
{
    sf::RenderWindow window(sf::VideoMode({1200, 800}), "GameEngine");
    sf::Clock clock;
    sf::Image icon("Assets/logo.png");

    if (!ImGui::SFML::Init(window)) {
        std::cerr << "Coudl'nt initialize ImGui" << std::endl;
        return (EXIT_FAILURE);
    }

    window.setIcon(icon);

    ImGuiWindowFlags wflags =
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoScrollWithMouse;

    en::EditorContext* context = en::CreateEditor();

    TKD::UClass myClass("MyClass");

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, clock.restart());

        en::SetCurrentEditor(context);

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

        ImGui::Begin("Main", nullptr, wflags);

        myClass.GetGraph()->Render();

        ImGui::End();

        en::SetCurrentEditor(nullptr);

        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }

    en::DestroyEditor(context);
    ImGui::SFML::Shutdown();

    return (0);
}
