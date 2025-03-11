///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "Utils/Utils.hpp"
#include "GraphEditor/GraphEditor.hpp"
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

    UEB::UClass myClass("MyClass");

    bool loadGraph = false;
    bool saveGraph = false;

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (auto key = event->getIf<sf::Event::KeyReleased>()) {
                if (key->code == sf::Keyboard::Key::L) loadGraph = true;
                if (key->code == sf::Keyboard::Key::S) saveGraph = true;
            }
        }

        ImGui::SFML::Update(window, clock.restart());

        en::SetCurrentEditor(context);

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

        ImGui::Begin("Main", nullptr, wflags);

        if (loadGraph) {
            UEB::ULoadArchive archive("MyClass.uassets");
            myClass.GetGraph()->Serialize(archive);
            loadGraph = false;
        }
        if (saveGraph) {
            UEB::USaveArchive archive("MyClass.uassets");
            myClass.GetGraph()->Serialize(archive);
            saveGraph = false;
        }

        ImGui::BeginTabBar("TabBar");

        if (ImGui::BeginTabItem("Play")) {
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Graph")) {
            myClass.GetGraph()->Render();
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();

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
