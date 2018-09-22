
// Author: Pierce Brooks

#include <STE/Intro.hpp>

STE::Intro::Intro(sf::RenderWindow* window) :
    State(INTRO_STATE_ID),
    isQuit(false)
{
    sf::Vector2f region = sf::Vector2f(window->getSize());
    quit = new Button(region*0.125f, "Quit", getFont(), sf::Color::Green, false);
    quit->setListener(this);
}

STE::Intro::~Intro()
{
    delete quit;
}

int STE::Intro::update(sf::RenderWindow* window, float deltaTime)
{
    if (isQuit)
    {
        isQuit = false;
        return MENU_STATE_ID;
    }
    quit->update(window, deltaTime);
    return NULL_STATE_ID;
}

void STE::Intro::didPress(Button* button)
{
    if (button == quit)
    {
        return;
    }
}

void STE::Intro::didRelease(Button* button)
{
    if (button == quit)
    {
        isQuit = true;
        return;
    }
}
