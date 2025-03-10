///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "GraphEditor/UNode.hpp"
#include "GraphEditor/UEvaluationContext.hpp"
#include "GraphEditor/UNodeBuilder.hpp"
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_node_editor.h>
#include <widgets.h>
#include <drawing.h>

///////////////////////////////////////////////////////////////////////////////
// Forward namespaces
///////////////////////////////////////////////////////////////////////////////
namespace ew = ax::Widgets;
namespace ed = ax::Drawing;
namespace en = ax::NodeEditor;

///////////////////////////////////////////////////////////////////////////////
// Namespace TKD
///////////////////////////////////////////////////////////////////////////////
namespace TKD
{

///////////////////////////////////////////////////////////////////////////////
FUint64 UNode::sNextID = 1;

///////////////////////////////////////////////////////////////////////////////
UNodeBuilder UNode::sBuilder;

///////////////////////////////////////////////////////////////////////////////
UNode::UNode(const FString& name, UNode::Type type, ImColor color)
    : mID(sNextID++)
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
    if (archive.IsLoading()) {
        return;
    }
    std::cout << "Getting position" << std::endl;
    ImVec2 position = en::GetNodePosition(mID);

    std::cout << "Registering name" << std::endl;
    archive << mRegister;
    std::cout << "Registering position" << std::endl;
    archive << position;
}

} // !namespace TKD
