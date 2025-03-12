///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "Objects/APawn.hpp"

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
    (void)key;
}

///////////////////////////////////////////////////////////////////////////////
void APawn::KeyReleased(sf::Keyboard::Key key)
{
    (void)key;
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
