///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "Utils/Strings/Strings.hpp"
#include "GraphEditor/Core/UGraph.hpp"
#include "GraphEditor/Core/UNodesRegister.hpp"
#include <imgui.h>
#include <imgui_stdlib.h>
#include <imgui_internal.h>
#include <imgui_node_editor.h>
#include <cctype>

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
UGraph::UGraph(void)
    : mCreating(false)
{}

///////////////////////////////////////////////////////////////////////////////
TSharedPtr<UPin> UGraph::FindPin(UPin::ID id)
{
    for (auto& node : mNodes) {
        for (auto& pin : node->GetInputs()) {
            if (pin->GetID() == id) {
                return (pin);
            }
        }
        for (auto& pin : node->GetOutputs()) {
            if (pin->GetID() == id) {
                return (pin);
            }
        }
    }

    return (nullptr);
}

///////////////////////////////////////////////////////////////////////////////
void UGraph::AddNode(TSharedPtr<UNode> node)
{
    if (!node) {
        return;
    }

    for (auto& pin : node->GetInputs()) {
        pin->SetOwner(node);
    }
    for (auto& pin : node->GetOutputs()) {
        pin->SetOwner(node);
    }

    mNodes.push_back(node);
}

///////////////////////////////////////////////////////////////////////////////
void UGraph::RemoveNode(TSharedPtr<UNode> node)
{
    auto it = std::find(mNodes.begin(), mNodes.end(), node);
    if (it != mNodes.end()) {
        mNodes.erase(it);
    }
}

///////////////////////////////////////////////////////////////////////////////
void UGraph::RemoveNode(UNode::ID id)
{
    auto it = std::find_if(mNodes.begin(), mNodes.end(),
        [id](const TSharedPtr<UNode>& node) {
            return (node->GetID() == id);
        });
    if (it != mNodes.end()) {
        mNodes.erase(it);
    }
}

///////////////////////////////////////////////////////////////////////////////
void UGraph::SetLink(TSharedPtr<UPin> source, TSharedPtr<UPin> target)
{
    TSharedPtr<ULink> link = std::make_shared<ULink>(source, target);
    link->Initialize();
    mLinks.push_back(link);
}

///////////////////////////////////////////////////////////////////////////////
void UGraph::RemoveLink(TSharedPtr<ULink> link)
{
    auto it = std::find(mLinks.begin(), mLinks.end(), link);
    if (it != mLinks.end()) {
        link->GetSource()->RemoveLink(link);
        link->GetTarget()->RemoveLink(link);
        mLinks.erase(it);
    }
}

///////////////////////////////////////////////////////////////////////////////
void UGraph::RemoveLink(ULink::ID id)
{
    auto it = std::find_if(mLinks.begin(), mLinks.end(),
        [id](const TSharedPtr<ULink>& link) {
            return (link->GetID() == id);
        });
    if (it != mLinks.end()) {
        mLinks.erase(it);
    }
}

///////////////////////////////////////////////////////////////////////////////
void UGraph::HandleCreate(void)
{
    if (en::BeginCreate(ImColor(255, 255, 255), 2.f)) {
        mCreating = true;
        UPin::ID sourceID = 0, targetID = 0;

        if (en::QueryNewLink(&sourceID, &targetID)) {
            TSharedPtr<UPin> source = FindPin(sourceID);
            TSharedPtr<UPin> target = FindPin(targetID);

            if (source->GetKind() == UPin::Kind::Input) {
                std::swap(source, target);
                std::swap(sourceID, targetID);
            }

            if (UPin::CanConnectTo(source, target)) {
                for (auto& link : target->GetLinks()) {
                    auto locked = link.lock();
                    if (locked && source->GetType() != UPin::Type::Flow) {
                        RemoveLink(locked);
                    }
                }
                SetLink(source, target);
            }
        }
    } else {
        mCreating = false;
    }
    en::EndCreate();
}

///////////////////////////////////////////////////////////////////////////////
void UGraph::HandleDelete(void)
{
    if (en::BeginDelete()) {
        UNode::ID nID;
        while (en::QueryDeletedNode(&nID)) {
            if (en::AcceptDeletedItem()) {
                RemoveNode(nID);
            }
        }

        ULink::ID lID;
        while (en::QueryDeletedLink(&lID)) {
            if (en::AcceptDeletedItem()) {
                RemoveLink(lID);
            }
        }
    }
    en::EndDelete();
}

///////////////////////////////////////////////////////////////////////////////
void UGraph::RenderGraphEditor(void)
{
    en::Begin("Graph Editor");

    for (auto& node : mNodes) {
        node->Render();
    }

    for (auto& link : mLinks) {
        en::Link(
            link->GetID(),
            link->GetSource()->GetID(),
            link->GetTarget()->GetID(),
            link->GetSource()->GetColor(),
            2.0f
        );
    }

    HandleCreate();
    HandleDelete();

    auto currentPosition = ImGui::GetMousePos();

    en::Suspend();

    if (en::ShowBackgroundContextMenu()) {
        ImGui::OpenPopup("CreateNewNode");
        if (mPopupOpened == false) {
            constexpr float size = 16.0f;
            float snapX = std::floor(currentPosition.x / size + 0.5f) * size;
            float snapY = std::floor(currentPosition.y / size + 0.5f) * size;
            mPosition = ImVec2(snapX, snapY);
            mPopupOpened = true;
            mSearch.clear();
        }
    } else {
        mPopupOpened = false;
    }

    en::Resume();

    en::Suspend();
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 8));

    if (ImGui::BeginPopup("CreateNewNode")) {
        ImGui::SetKeyboardFocusHere();
        ImGui::InputText("##CreateNodeSearch", &mSearch);
        ImGui::Separator();

        TVector<FString> names = UNodesRegister::GetNames();

        TVector<FString> tokens = String::Tokenize(
            String::ToLower(String::Trim(mSearch))
        );

        for (const auto& name : names) {
            bool matchToken = true;

            std::string nameLower = String::ToLower(name);

            for (const auto& token : tokens) {
                if (nameLower.find(token) == FString::npos) {
                    matchToken = false;
                    break;
                }
            }

            if (matchToken) {
                if (ImGui::MenuItem(name.c_str())) {
                    AddNode(UNodesRegister::Create(name));
                    en::SetNodePosition(mNodes.back()->GetID(), mPosition);
                }
            }
        }

        ImGui::EndPopup();
    }

    ImGui::PopStyleVar();

    en::Resume();

    en::End();
}

///////////////////////////////////////////////////////////////////////////////
void UGraph::Render(void)
{
    const float propertyBarWidth = 400.0f;

    // Change the property bar color to rgb(21, 21, 21)
    float c21 = 21.f / 255.f;
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(c21, c21, c21, 1.0f));

    ImGui::BeginChild("PropertyBar", ImVec2(propertyBarWidth, -1));

    // Changing the header background color rgb(47, 47, 47)
    float c47 = 47.f / 255.f;
    ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(c47, c47, c47, 1.0f));

    if (ImGui::CollapsingHeader("Graphs", ImGuiTreeNodeFlags_DefaultOpen)) {
    }

    if (ImGui::CollapsingHeader("Functions", ImGuiTreeNodeFlags_DefaultOpen)) {
    }

    if (ImGui::CollapsingHeader("Variables", ImGuiTreeNodeFlags_DefaultOpen)) {
    }

    ImGui::PopStyleColor();

    ImGui::EndChild();

    ImGui::PopStyleColor();

    ImGui::SameLine();

    ImGui::BeginChild("NodeGraph", ImVec2(0, 0), false,
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    RenderGraphEditor();

    ImGui::EndChild();
}

///////////////////////////////////////////////////////////////////////////////
void UGraph::Serialize(UArchive& archive)
{
    if (archive.IsLoading()) {
        mNodes.clear();
        mLinks.clear();

        FUint64 size = 0;
        archive << size;

        for (FUint64 i = 0; i < size; i++) {
            FString nodeName = "";
            ImVec2 nodePosition = ImVec2(0, 0);

            archive << nodeName << nodePosition;

            AddNode(UNodesRegister::Create(nodeName));
            en::SetNodePosition(mNodes.back()->GetID(), nodePosition);
        }

        // TODO: Load the links

    } else if (archive.IsSaving()) {

        FUint64 size = mNodes.size();
        archive << size;
        for (auto& node : mNodes) {
            node->Serialize(archive);
        }

        // TODO: Save the links
    }
}

///////////////////////////////////////////////////////////////////////////////
void UGraph::Execute(TSharedPtr<UNode> node, UEvaluationContext& context)
{
    if (!node) {
        return;
    }

    context.Reset();
    context.AddToEvaluationQueue(node);

    while (!context.IsQueueEmpty()) {
        auto node = context.GetNextNode().lock();

        if (!node) {
            continue;
        }

        if (!context.IsEvaluated(node)) {
            node->Evaluate(context);
            context.MarkAsEvaluated(node);
        }

        for (auto& pin : node->GetOutputs()) {
            if (
                pin->GetType() != UPin::Type::Flow ||
                context.GetPinValue<bool>(pin) == false
            ) {
                continue;
            }

            for (auto& wlink : pin->GetLinks()) {
                TSharedPtr<ULink> link = wlink.lock();
                if (!link) {
                    continue;
                }

                TSharedPtr<UPin> target = link->GetTarget();

                context.AddToEvaluationQueue(target->GetOwner());
            }
        }
    }
}

} // !namespace UEB
