
// Author: Pierce Brooks

#include <STE/Date.hpp>
#include <iostream>

std::map<int, std::string>* STE::Date::dates = nullptr;

STE::Date::Date(sf::RenderWindow* window, int type) :
    State(type),
    isQuit(false)
{
    sf::Vector2f region = sf::Vector2f(window->getSize());
    std::string date = getDate(type);
    if (date.empty())
    {
        std::cout << "Invalid date!" << std::endl;
        dialogue = nullptr;
    }
    else
    {
        dialogue = new Dialogue(window, "./Assets/Dialogue/"+date, this);
    }
    quit = new Button(region*BUTTON_SCALE, "Quit", getFont(), DEFAULT_TEXT_COLOR, false);
    quit->setListener(this);
}

STE::Date::~Date()
{
    delete quit;
}

int STE::Date::update(sf::RenderWindow* window, float deltaTime)
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

std::string STE::Date::getDate(int type)
{
    std::map<int, std::string>::iterator iter = dates->find(type);
    if (iter != dates->end())
    {
        return iter->second;
    }
    return "";
}

void STE::Date::loadDates()
{
    if (dates != nullptr)
    {
        return;
    }
    dates = new std::map<int, std::string>();
    (*dates)[FIRE_STATE_ID] = "fire_dialogue.txt";
    (*dates)[WATER_STATE_ID] = "water_dialogue.txt";
    (*dates)[EARTH_STATE_ID] = "earth_dialogue.txt";
    (*dates)[AIR_STATE_ID] = "air_dialogue.txt";
}

void STE::Date::unloadDates()
{
    if (dates == nullptr)
    {
        return;
    }
    dates->clear();
    delete dates;
    dates = nullptr;
}

void STE::Date::didPress(Button* button)
{
    if (button == quit)
    {
        return;
    }
}

void STE::Date::didRelease(Button* button)
{
    if (button == quit)
    {
        isQuit = true;
        return;
    }
}
