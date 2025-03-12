///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "GraphEditor/Core/UPin.hpp"
#include "GraphEditor/Core/UNode.hpp"
#include "GraphEditor/Core/UNodeBuilder.hpp"
#include "GraphEditor/Core/ULink.hpp"
#include "Utils/SVG.hpp"
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
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
//
///////////////////////////////////////////////////////////////////////////////
static const sf::Texture PinIcons[4] = {
    LoadSVG("Source/Content/Icons/Pins/Flow.svg", 48, 48),
    LoadSVG("Source/Content/Icons/Pins/FlowConnected.svg", 48, 48),
    LoadSVG("Source/Content/Icons/Pins/Pin.svg", 48, 48),
    LoadSVG("Source/Content/Icons/Pins/PinConnected.svg", 48, 48)
};

///////////////////////////////////////////////////////////////////////////////
UPin::UPin(UPin::Type type, UPin::Kind kind, const FString& name)
    : mType(type)
    , mKind(kind)
    , mID(UNode::sNextID++)
    , mName(name)
{}

///////////////////////////////////////////////////////////////////////////////
bool UPin::CanConnectTo(TSharedPtr<UPin> a, TSharedPtr<UPin> b)
{
    bool canConnect = false;

    auto ShowLabel = [](
            const char* label,
            const ImColor& color = ImColor(45, 32, 32, 180)
    ) {
        ImGui::SetCursorPosY(
            ImGui::GetCursorPosY() - ImGui::GetTextLineHeight()
        );
        auto size = ImGui::CalcTextSize(label);

        auto padding = ImGui::GetStyle().FramePadding;
        auto spacing = ImGui::GetStyle().ItemSpacing;

        ImGui::SetCursorPos(
            ImGui::GetCursorPos() + ImVec2(spacing.x, -spacing.y)
        );

        auto rectMin = ImGui::GetCursorScreenPos() - padding;
        auto rectMax = ImGui::GetCursorScreenPos() + size + padding;

        auto drawList = ImGui::GetWindowDrawList();
        drawList->AddRectFilled(rectMin, rectMax, color, size.y * 0.15f);
        ImGui::TextUnformatted(label);
    };

    if (!(canConnect = ((a && b) || (a == b)))) {
    } else if (!(canConnect = (a->GetType() == b->GetType()))) {
        ShowLabel("x Incompatible Pin Type");
    } else if (!(canConnect = (a->GetKind() != b->GetKind()))) {
        ShowLabel("x Incompatible Pin Kind");
    } else if (a->GetType() == UPin::Type::Flow &&
        !(canConnect = (a->GetLinks().size() == 0))) {
        ShowLabel("x Flow Pin Already Connected");
    }

    if (!canConnect) {
        en::RejectNewItem(ImColor(255, 128, 128), 1.0f);
        return (false);
    }
    ShowLabel("+ Create Link", ImColor(32, 45, 32, 180));
    return (en::AcceptNewItem(ImColor(128, 255, 128), 4.0f));
}

///////////////////////////////////////////////////////////////////////////////
void UPin::DrawPinIcon(float alpha)
{
    ImColor color = GetColor();
    bool connected = !mLinks.empty();
    sf::Color clr(
        color.Value.x * 255,
        color.Value.y * 255,
        color.Value.z * 255,
        alpha * 255
    );

    if (mType == Type::Flow) {
        ImGui::Image(PinIcons[0 + connected], sf::Vector2f(16, 16), clr);
    } else {
        ImGui::Image(PinIcons[2 + connected], sf::Vector2f(16, 16), clr);
    }
}

///////////////////////////////////////////////////////////////////////////////
ImColor UPin::GetColor(void) const
{
    switch (mType) {
        case Type::Float:                      return (ImColor(151, 250,  61));
        case Type::Integer:                    return (ImColor( 40, 224, 172));
        case Type::Integer64:                  return (ImColor(169, 226, 173));
        case Type::Boolean:                    return (ImColor(149,   0,   2));
        case Type::Byte:                       return (ImColor(  0, 110, 101));
        case Type::String:                     return (ImColor(239,   2, 204));
        case Type::Vector:                     return (ImColor(246, 195,  33));
        case Type::Actor:                      return (ImColor(  0, 168, 242));
        default:                               return (ImColor(255, 255, 255));
    }
}

///////////////////////////////////////////////////////////////////////////////
UPin::Type UPin::GetType(void) const
{
    return (mType);
}

///////////////////////////////////////////////////////////////////////////////
UPin::Kind UPin::GetKind(void) const
{
    return (mKind);
}

///////////////////////////////////////////////////////////////////////////////
UPin::ID UPin::GetID(void) const
{
    return (mID);
}

///////////////////////////////////////////////////////////////////////////////
FString UPin::GetName(void) const
{
    return (mName);
}

///////////////////////////////////////////////////////////////////////////////
const TVector<TWeakPtr<ULink>>& UPin::GetLinks(void) const
{
    return (mLinks);
}

///////////////////////////////////////////////////////////////////////////////
void UPin::SetOwner(TWeakPtr<UNode> owner)
{
    mOwner = owner;
}

///////////////////////////////////////////////////////////////////////////////
TSharedPtr<UNode> UPin::GetOwner(void) const
{
    return (mOwner.lock());
}

///////////////////////////////////////////////////////////////////////////////
void UPin::AddLink(TWeakPtr<ULink> link)
{
    auto it = std::find_if(mLinks.begin(), mLinks.end(),
        [&link](const TWeakPtr<ULink>& existingLink) {
            return (existingLink.lock() == link.lock());
        });
    if (it == mLinks.end()) {
        mLinks.push_back(link);
    }
}

///////////////////////////////////////////////////////////////////////////////
void UPin::RemoveLink(TWeakPtr<ULink> link)
{
    auto it = std::find_if(mLinks.begin(), mLinks.end(),
        [&link](const TWeakPtr<ULink>& existingLink) {
            return (existingLink.lock() == link.lock());
        });
    if (it != mLinks.end()) {
        mLinks.erase(it);
    }
}

///////////////////////////////////////////////////////////////////////////////
void UPin::Render(void)
{
    auto alpha = ImGui::GetStyle().Alpha;

    // TODO: Change the alpha when creating a link and this pin is compatible

    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, alpha);

    if (mKind == Kind::Input) {
        UNode::sBuilder.Input(mID);

        DrawPinIcon(alpha);

        ImGui::Spring(0);
        if (!mName.empty()) {
            ImGui::TextUnformatted(mName.c_str());
            ImGui::Spring(0);
        }

        ImGui::PopStyleVar();
        UNode::sBuilder.EndInput();
    } else {
        UNode::sBuilder.Output(mID);

        if (!mName.empty()) {
            ImGui::Spring(0);
            ImGui::TextUnformatted(mName.c_str());
        }
        ImGui::Spring(0);

        DrawPinIcon(alpha);

        ImGui::PopStyleVar();
        UNode::sBuilder.EndOutput();
    }
}

} // !namespace UEB
