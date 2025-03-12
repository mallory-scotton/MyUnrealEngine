///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "GraphEditor/Core/UNode.hpp"
#include "GraphEditor/Core/UEvaluationContext.hpp"
#include "GraphEditor/Core/UNodeBuilder.hpp"
#include "Content/Icons/Nodes.hpp"
#include <imgui-SFML.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_node_editor.h>

///////////////////////////////////////////////////////////////////////////////
// Forward namespaces
///////////////////////////////////////////////////////////////////////////////
namespace en = ax::NodeEditor;

///////////////////////////////////////////////////////////////////////////////
// Namespace UEB
///////////////////////////////////////////////////////////////////////////////
namespace UEB
{

///////////////////////////////////////////////////////////////////////////////
FUint64 UNode::sNextID = 1;

///////////////////////////////////////////////////////////////////////////////
UNodeBuilder UNode::sBuilder;

///////////////////////////////////////////////////////////////////////////////
static const sf::Texture Icons[static_cast<int>(UNode::NodeIcon::COUNT)] = {
    sf::Texture(Icon::Branch, sizeof(Icon::Branch)),        // Branch
    sf::Texture(),                                          // Select
    sf::Texture(Icon::Sequence, sizeof(Icon::Sequence)),    // Sequence
    sf::Texture(),                                          // FliFlop
    sf::Texture(),                                          // DoN
    sf::Texture(),                                          // DoOnce
    sf::Texture(),                                          // ForEach
    sf::Texture(Icon::Event, sizeof(Icon::Event)),          // Event
    sf::Texture(),                                          // Cast
    sf::Texture()                                           // BreakStructure
};

///////////////////////////////////////////////////////////////////////////////
UNode::UNode(
    const FString& name,
    UNode::Type type,
    ImColor color,
    NodeIcon icon
)
    : mID(sNextID++)
    , mIcon(icon)
    , mName(name)
    , mType(type)
    , mColor(color)
    , mCanAddPin(false)
{}

///////////////////////////////////////////////////////////////////////////////
void UNode::OnPinAdded(void)
{}

///////////////////////////////////////////////////////////////////////////////
void UNode::AddInputPin(TSharedPtr<UPin> pin)
{
    mInputs.push_back(std::move(pin));
}

///////////////////////////////////////////////////////////////////////////////
void UNode::AddInputPin(UPin::Type type, const FString& name)
{
    AddInputPin(std::make_shared<UPin>(type, UPin::Kind::Input, name));
}

///////////////////////////////////////////////////////////////////////////////
void UNode::AddOutputPin(TSharedPtr<UPin> pin)
{
    mOutputs.push_back(std::move(pin));
}

///////////////////////////////////////////////////////////////////////////////
void UNode::AddOutputPin(UPin::Type type, const FString& name)
{
    AddOutputPin(std::make_shared<UPin>(type, UPin::Kind::Output, name));
}

///////////////////////////////////////////////////////////////////////////////
UNode::ID UNode::GetID(void) const
{
    return (mID);
}

///////////////////////////////////////////////////////////////////////////////
FString UNode::GetName(void) const
{
    return (mName);
}

///////////////////////////////////////////////////////////////////////////////
UNode::Type UNode::GetType(void) const
{
    return (mType);
}

///////////////////////////////////////////////////////////////////////////////
const UNode::PinList& UNode::GetInputs(void) const
{
    return (mInputs);
}

///////////////////////////////////////////////////////////////////////////////
const UNode::PinList& UNode::GetOutputs(void) const
{
    return (mOutputs);
}

///////////////////////////////////////////////////////////////////////////////
void UNode::SetRegister(const FString& reg)
{
    mRegister = reg;
}

///////////////////////////////////////////////////////////////////////////////
void UNode::Render(void)
{
    sBuilder.Begin(mID);

    if (mType != Type::Simple) {
        sBuilder.Header(mColor);
        if (mIcon != NodeIcon::None) {
            ImGui::Image(Icons[static_cast<int>(mIcon)], sf::Vector2f(16, 16));
        }
        ImGui::Spring(0);
        ImGui::TextUnformatted(mName.c_str());
        ImGui::Spring(1);
        ImGui::Dummy(ImVec2(0, 28));
        ImGui::Spring();
        sBuilder.EndHeader();
    }

    for (auto& input : mInputs) {
        input->Render();
    }

    if (mType == Type::Simple) {
        sBuilder.Middle();
        ImGui::Spring(1, 0);
        ImGui::SetWindowFontScale(2.0f);
        ImGui::TextUnformatted(mName.c_str());
        ImGui::SetWindowFontScale(1.0f);
        ImGui::Spring(1, 0);
    }

    for (auto& output : mOutputs) {
        output->Render();
    }

    // TODO: Add the possibility to add new pin

    sBuilder.End();
}

///////////////////////////////////////////////////////////////////////////////
void UNode::Serialize(UArchive& archive)
{
    if (!archive.IsSaving()) {
        return;
    }
    ImVec2 position = en::GetNodePosition(mID);
    archive << mRegister << position;
}

} // !namespace UEB
