
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
    quit = new Button(region*0.125f, "Quit", getFont(), DEFAULT_TEXT_COLOR, false);
    quit->setListener(this);
}

STE::Date::~Date()
{
    delete quit;
}

int STE::Date::update(sf::RenderWindow* window, float deltaTime)
{
    mouse();
    if (isQuit)
    {
        isQuit = false;
        return MENU_STATE_ID;
    }
    if (dialogue == nullptr)
    {
        return INVALID_STATE_ID;
    }
    if (dialogue->update(window, deltaTime) < 0)
    {
        return INVALID_STATE_ID;
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
    (*dates)[FIRE_STATE_ID] = "Fire";
    (*dates)[WATER_STATE_ID] = "Water";
    (*dates)[EARTH_STATE_ID] = "Earth";
    (*dates)[AIR_STATE_ID] = "Air";
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
