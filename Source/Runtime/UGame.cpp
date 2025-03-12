///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "Runtime/UGame.hpp"

///////////////////////////////////////////////////////////////////////////////
// Namespace UEB
///////////////////////////////////////////////////////////////////////////////
namespace UEB
{

///////////////////////////////////////////////////////////////////////////////
UGame::UGame(TSharedPtr<UEB::UWorld> world)
    : mWorld(world)
    , mClosed(true)
{}

///////////////////////////////////////////////////////////////////////////////
UGame::~UGame()
{
    Close();
}

///////////////////////////////////////////////////////////////////////////////
void UGame::Initialize(void)
{
    mWindow = std::make_unique<sf::RenderWindow>(
        sf::VideoMode({800, 600}), "UEB", sf::Style::Close);
    mClock = std::make_unique<sf::Clock>();
    mClosed = false;
    if (mWorld) {
        mWorld->BeginPlay();
    }
}

///////////////////////////////////////////////////////////////////////////////
void UGame::Run(void)
{
    if (mClosed || !mWindow || !mWindow->isOpen() || !mWorld) {
        return;
    }

    while (const auto& event = mWindow->pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            Close();
        } else if (const auto& key = event->getIf<sf::Event::KeyPressed>()) {
            mWorld->KeyPressed(key->code);
        } else if (const auto& key = event->getIf<sf::Event::KeyReleased>()) {
            mWorld->KeyReleased(key->code);
        }
    }

    mWorld->Tick(mClock->restart().asSeconds());

    mWindow->clear();
    mWorld->Render(*mWindow);
    mWindow->display();
}

///////////////////////////////////////////////////////////////////////////////
bool UGame::IsClosed(void) const
{
    return (mClosed);
}

///////////////////////////////////////////////////////////////////////////////
void UGame::Close(void)
{
    if (mClosed == true) {
        return;
    }
    if (mWorld) {
        mWorld->EndPlay();
    }
    if (mWindow && mWindow->isOpen()) {
        mWindow->close();
    }
    mClosed = true;
}

} // !namespace UEB
