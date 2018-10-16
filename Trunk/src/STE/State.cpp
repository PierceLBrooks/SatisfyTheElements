
// Author: Pierce Brooks

#include <STE/State.hpp>
#include <SFML/Window/Mouse.hpp>

STE::State::State(int id) :
    Entity(),
    id(id),
    isPressed(false),
    isReleased(false)
{
    font = new sf::Font();
    font->loadFromFile(getAssetsPath()+"Fonts/Arial/arial.ttf");
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

bool STE::State::getIsPressed() const
{
    return isPressed;
}

bool STE::State::getIsReleased() const
{
    return isReleased;
}

int STE::State::update(sf::RenderWindow* window, float deltaTime)
{
    mouse(window);
}

void STE::State::start()
{

}

void STE::State::mouse(sf::RenderWindow* window)
{
    if (isReleased)
    {
        isReleased = false;
    }
    if (!sf::FloatRect(window->getView().getCenter()-(window->getView().getSize()*0.5f), window->getView().getSize()).contains(sf::Vector2f(sf::Mouse::getPosition(*window))))
    {
        return;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        if (!isPressed)
        {
            isPressed = true;
        }
    }
    else
    {
        if (isPressed)
        {
            isPressed = false;
            isReleased = true;
        }
    }
}

void STE::State::didPress(Button* button)
{

}

void STE::State::didRelease(Button* button)
{

}
