///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "Objects/APawn.hpp"
#include "GraphEditor/Nodes/EventNodes.hpp"
#include "Utils/SFML/Enumerations.hpp"

///////////////////////////////////////////////////////////////////////////////
// Namespace UEB
///////////////////////////////////////////////////////////////////////////////
namespace UEB
{

///////////////////////////////////////////////////////////////////////////////
APawn::APawn(TSharedPtr<UClass> inClass)
    : AActor(inClass)
{}

///////////////////////////////////////////////////////////////////////////////
void APawn::KeyPressed(sf::Keyboard::Key key)
{
    FString name = KeyNames[static_cast<int>(key)];
    auto eventNode = mClass->GetGraph()->FindEventNode<Nodes::KeyNode>(name);

    if (eventNode) {
        mContext.SetPinValue(eventNode->GetOutputs()[0], true);
        mContext.SetPinValue(eventNode->GetOutputs()[1], false);
        mClass->GetGraph()->Execute(eventNode, mContext);
    }
}

///////////////////////////////////////////////////////////////////////////////
void APawn::KeyReleased(sf::Keyboard::Key key)
{
    FString name = KeyNames[static_cast<int>(key)];
    auto eventNode = mClass->GetGraph()->FindEventNode<Nodes::KeyNode>(name);

    if (eventNode) {
        mContext.SetPinValue(eventNode->GetOutputs()[0], false);
        mContext.SetPinValue(eventNode->GetOutputs()[1], true);
        mClass->GetGraph()->Execute(eventNode, mContext);
    }
}

///////////////////////////////////////////////////////////////////////////////
void APawn::Render(sf::RenderTarget& target) const
{
    sf::RectangleShape shape({20, 20});
    shape.setFillColor(sf::Color::Red);
    shape.setScale(mScale);
    shape.setPosition(mPosition);
    target.draw(shape);
}

} // !namespace UEB
