
// Author: Pierce Brooks

#include <STE/Intro.hpp>

STE::Intro::Intro(sf::RenderWindow* window) :
    State(INTRO_STATE_ID),
    isQuit(false)
{
    sf::Vector2f region = sf::Vector2f(window->getSize());
    dialogue = new Dialogue(window, "./Assets/Dialogue/water_dialogue.txt", this);
    quit = new Button(region*BUTTON_SCALE, "Quit", getFont(), DEFAULT_TEXT_COLOR, false);
    quit->setListener(this);
}

STE::Intro::~Intro()
{
    delete dialogue;
    delete quit;
}

int STE::Intro::update(sf::RenderWindow* window, float deltaTime)
{
    if (isQuit)
    {
        isQuit = false;
        return MENU_STATE_ID;
    }
    if (dialogue->update(window, deltaTime) < 0)
    {
        return INVALID_STATE_ID;
    }
    int buttons = 0;
    buttons |= quit->update(window, deltaTime);
    if (buttons == 0)
    {
        mouse();
        if (getIsReleased())
        {
            if (!dialogue->show())
            {
                return CLIENT_SELECTION_STATE_ID;
            }
        }
    }
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
