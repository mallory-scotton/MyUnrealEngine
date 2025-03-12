///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "Utils/Utils.hpp"
#include "GraphEditor/GraphEditor.hpp"
#include "Runtime/UGame.hpp"
#include "Objects/APawn.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui-SFML.h>
#include <imgui_node_editor.h>

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

    ImGuiIO& io = ImGui::GetIO();

    ImFontConfig fontConfig;
    fontConfig.OversampleH = 4;
    fontConfig.OversampleV = 4;
    fontConfig.PixelSnapH = true;

    ImFont* font = io.Fonts->AddFontFromFileTTF(
        "Source/Content/Fonts/Roboto-Medium.ttf", 
        16.0f,
        &fontConfig
    );
    
    if (font) {
        io.FontDefault = font;
        io.FontGlobalScale = 1.0f;
        (void)ImGui::SFML::UpdateFontTexture();
    } else {
        std::cerr << "Failed to load Roboto-Medium.ttf font" << std::endl;
    }

    TSharedPtr<UEB::UClass> myClass = std::make_shared<UEB::UClass>("MyClass");

    bool loadGraph = false;
    bool saveGraph = false;

    TSharedPtr<UEB::UWorld> world = std::make_shared<UEB::UWorld>();
    TUniquePtr<UEB::UGame> game;
    TSharedPtr<UEB::APawn> pawn = std::make_shared<UEB::APawn>(myClass);
    world->AddObject(pawn);

    pawn->SetLocation({200.f, 200.f});

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
            myClass->GetGraph()->Serialize(archive);
            loadGraph = false;
        }
        if (saveGraph) {
            UEB::USaveArchive archive("MyClass.uassets");
            myClass->GetGraph()->Serialize(archive);
            saveGraph = false;
        }

        ImGui::BeginTabBar("TabBar");

        if (ImGui::BeginTabItem("Play")) {
            if (ImGui::Button("Play") && !game) {
                game = std::make_unique<UEB::UGame>(world);
                game->Initialize();
            }
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Graph")) {
            myClass->GetGraph()->Render();
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();

        ImGui::End();

        en::SetCurrentEditor(nullptr);

        if (game) {
            if (game->IsClosed()) {
                game = nullptr;
            } else {
                game->Run();
            }
        }

        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }

    en::DestroyEditor(context);
    ImGui::SFML::Shutdown();

    return (0);
}
