///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "GraphEditor/Core/UNodeBuilder.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <imgui_node_editor.h>
#include <widgets.h>
#include <drawing.h>
#include <cstring>

///////////////////////////////////////////////////////////////////////////////
// Forward namespaces
///////////////////////////////////////////////////////////////////////////////
namespace ew = ax::Widgets;
namespace ed = ax::Drawing;
namespace en = ax::NodeEditor;

ImTextureID sfToImGuiTexture(GLuint glTextureHandle)
{
    ImTextureID textureID{};
    std::memcpy(&textureID, &glTextureHandle, sizeof(GLuint));
    return (textureID);
}

///////////////////////////////////////////////////////////////////////////////
// Namespace UEB
///////////////////////////////////////////////////////////////////////////////
namespace UEB
{

///////////////////////////////////////////////////////////////////////////////
UNodeBuilder::UNodeBuilder(void)
    : mHeaderTexture(nullptr)
    , mHeaderWidth(0)
    , mHeaderHeight(0)
    , mID(0)
    , mStage(Stage::Invalid)
    , mHasHeader(false)
{
    if (mTexture.loadFromFile("Assets/BlueprintNoise.png")) {
        mHeaderTexture = sfToImGuiTexture(mTexture.getNativeHandle());
        mHeaderWidth = mTexture.getSize().x;
        mHeaderHeight = mTexture.getSize().y;
    }
}

///////////////////////////////////////////////////////////////////////////////
UNodeBuilder::~UNodeBuilder(void)
{}

///////////////////////////////////////////////////////////////////////////////
void UNodeBuilder::SetStage(Stage stage)
{
    if (mStage == stage) {
        return;
    }

    Stage oStage = mStage;
    mStage = stage;

    switch (oStage) {
        case Stage::Begin:
        case Stage::Content:
        case Stage::End:
        case Stage::Invalid:
            break;
        case Stage::Header:
            ImGui::EndHorizontal();
            mHeaderMin = ImGui::GetItemRectMin();
            mHeaderMax = ImGui::GetItemRectMax();
            ImGui::Spring(0, ImGui::GetStyle().ItemSpacing.y * 2.f);
            break;
        case Stage::Input:
        case Stage::Output:
            en::PopStyleVar(2);
            ImGui::Spring(1, 0);
            ImGui::EndVertical();
            break;
        case Stage::Middle:
            ImGui::EndVertical();
            break;
    }

    switch (stage) {
        case Stage::Begin:
            ImGui::BeginVertical("node");
            break;
        case Stage::Header:
            mHasHeader = true;
            ImGui::BeginHorizontal("header");
            break;
        case Stage::Content:
            if (oStage == Stage::Begin) {
                ImGui::Spring(0);
            }
            ImGui::BeginHorizontal("content");
            ImGui::Spring(0, 0);
            break;
        case Stage::Input:
            ImGui::BeginVertical("inputs", ImVec2(0, 0), 0.f);
            en::PushStyleVar(en::StyleVar_PivotAlignment, ImVec2(0, 0.5f));
            en::PushStyleVar(en::StyleVar_PivotSize, ImVec2(0, 0));
            if (!mHasHeader) {
                ImGui::Spring(1, 0);
            }
            break;
        case Stage::Middle:
            ImGui::Spring(1);
            ImGui::BeginVertical("middle", ImVec2(0, 0), 1.0f);
            break;
        case Stage::Output:
            if (oStage == Stage::Middle || oStage == Stage::Input) {
                ImGui::Spring(1);
            } else {
                ImGui::Spring(1, 0);
            }
            ImGui::BeginVertical("outputs", ImVec2(0, 0), 1.f);
            en::PushStyleVar(en::StyleVar_PivotAlignment, ImVec2(1.0f, 0.5f));
            en::PushStyleVar(en::StyleVar_PivotSize, ImVec2(0, 0));
            if (!mHasHeader) {
                ImGui::Spring(1, 0);
            }
            break;
        case Stage::End:
            if (oStage == Stage::Input) {
                ImGui::Spring(1, 0);
            }
            if (oStage != Stage::Begin) {
                ImGui::EndHorizontal();
            }
            mContentMin = ImGui::GetItemRectMin();
            mContentMax = ImGui::GetItemRectMax();
            ImGui::EndVertical();
            mNodeMin = ImGui::GetItemRectMin();
            mNodeMax = ImGui::GetItemRectMax();
            break;
        case Stage::Invalid:
            break;
    }
}

///////////////////////////////////////////////////////////////////////////////
void UNodeBuilder::Begin(UNode::ID id)
{
    mHasHeader = false;
    mHeaderMin = mHeaderMax = ImVec2(0, 0);
    mID = id;

    en::PushStyleVar(en::StyleVar_NodePadding, ImVec4(8, 4, 8, 8));
    en::BeginNode(id);
    ImGui::PushID(id.AsPointer());
    SetStage(Stage::Begin);
}

///////////////////////////////////////////////////////////////////////////////
void UNodeBuilder::End(void)
{
    SetStage(Stage::End);
    en::EndNode();

    if (ImGui::IsItemVisible()) {
        auto alpha = static_cast<int>(255 * ImGui::GetStyle().Alpha);
        auto drawList = en::GetNodeBackgroundDrawList(mID);
        const auto halfBorderWidth = en::GetStyle().NodeBorderWidth * 0.5f;
        auto headerColor =
            IM_COL32(0, 0, 0, alpha) |
            (mHeaderColor & IM_COL32(255, 255, 255, 0));

        if (
            (mHeaderMax.x > mHeaderMin.x) &&
            (mHeaderMax.y > mHeaderMin.y) &&
            mHeaderTexture
        ) {
            const auto uv = ImVec2(
                (mHeaderMax.x - mHeaderMin.x) / (float)(4.0f * mHeaderWidth),
                (mHeaderMax.y - mHeaderMin.y) / (float)(4.0f * mHeaderHeight));

            drawList->AddImageRounded(mHeaderTexture,
                mHeaderMin - ImVec2(8 - halfBorderWidth, 4 - halfBorderWidth),
                mHeaderMax + ImVec2(8 - halfBorderWidth, 0),
                ImVec2(0.0f, 0.0f), uv,
                headerColor, en::GetStyle().NodeRounding,
                ImDrawFlags_RoundCornersTop
            );

            if (mContentMin.y > mHeaderMax.y) {
                drawList->AddLine(
                    ImVec2(
                        mHeaderMin.x - (8 - halfBorderWidth),
                        mHeaderMax.y - 0.5f
                    ),
                    ImVec2(
                        mHeaderMax.x + (8 - halfBorderWidth),
                        mHeaderMax.y - 0.5f
                    ),
                    ImColor(255, 255, 255, 96 * alpha / (3 * 255)),
                    1.0f
                );
            }
        }
    }

    mID = 0;
    ImGui::PopID();
    en::PopStyleVar();
    SetStage(Stage::Invalid);
}

///////////////////////////////////////////////////////////////////////////////
void UNodeBuilder::Header(const ImVec4& color)
{
    mHeaderColor = ImColor(color);
    SetStage(Stage::Header);
}

///////////////////////////////////////////////////////////////////////////////
void UNodeBuilder::EndHeader(void)
{
    SetStage(Stage::Content);
}

///////////////////////////////////////////////////////////////////////////////
void UNodeBuilder::Input(UPin::ID id)
{
    if (mStage == Stage::Begin) {
        SetStage(Stage::Content);
    }
    const bool hasPadding = (mStage == Stage::Input);
    SetStage(Stage::Input);
    if (hasPadding) {
        ImGui::Spring(0);
    }
    en::BeginPin(id, UPin::Kind::Input);
    ImGui::BeginHorizontal(id.AsPointer());
}

///////////////////////////////////////////////////////////////////////////////
void UNodeBuilder::EndInput(void)
{
    ImGui::EndHorizontal();
    en::EndPin();
}

///////////////////////////////////////////////////////////////////////////////
void UNodeBuilder::Output(UPin::ID id)
{
    if (mStage == Stage::Begin) {
        SetStage(Stage::Content);
    }
    const bool hasPadding = (mStage == Stage::Output);
    SetStage(Stage::Output);
    if (hasPadding) {
        ImGui::Spring(0);
    }
    en::BeginPin(id, UPin::Kind::Output);
    ImGui::BeginHorizontal(id.AsPointer());
}

///////////////////////////////////////////////////////////////////////////////
void UNodeBuilder::EndOutput(void)
{
    ImGui::EndHorizontal();
    en::EndPin();
}

///////////////////////////////////////////////////////////////////////////////
void UNodeBuilder::Middle(void)
{
    if (mStage == Stage::Begin) {
        SetStage(Stage::Content);
    }
    SetStage(Stage::Middle);
}

} // !namespace UEB
