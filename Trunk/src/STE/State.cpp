
// Author: Pierce Brooks

#include <STE/State.hpp>

STE::State::State(int id) :
    Entity(),
    id(id)
{
    font = new sf::Font();
    font->loadFromFile("./Assets/Fonts/Tangerine/Tangerine_Bold.ttf");
}

STE::State::~State()
{
    delete font;
}

int STE::State::getID() const
{
    return id;
}

sf::Font* STE::State::getFont() const
{
    return font;
}

int STE::State::update(sf::RenderWindow* window, float deltaTime)
{

}

void STE::State::didPress(Button* button)
{

}

void STE::State::didRelease(Button* button)
{

}
