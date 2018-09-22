
// Author: Pierce Brooks

#include <STE/ClientSelection.hpp>

STE::ClientSelection::ClientSelection(sf::RenderWindow* window) :
    State(CLIENT_SELECTION_STATE_ID),
    isQuit(false),
    isFire(false),
    isWater(false),
    isEarth(false),
    isAir(false)
{
    sf::Vector2f region = sf::Vector2f(window->getSize());
    quit = new Button(region*0.125f, "Quit", getFont(), sf::Color::Green, false);
    quit->setListener(this);
    fire = new Button(region*0.125f, "Fire", getFont(), sf::Color::Green, false);
    fire->setListener(this);
    water = new Button(region*0.125f, "Water", getFont(), sf::Color::Green, false);
    water->setListener(this);
    earth = new Button(region*0.125f, "Earth", getFont(), sf::Color::Green, false);
    earth->setListener(this);
    air = new Button(region*0.125f, "Air", getFont(), sf::Color::Green, false);
    air->setListener(this);
}

STE::ClientSelection::~ClientSelection()
{
    delete quit;
    delete fire;
    delete water;
    delete earth;
    delete air;
}

int STE::ClientSelection::update(sf::RenderWindow* window, float deltaTime)
{
    if (isQuit)
    {
        isQuit = false;
        return MENU_STATE_ID;
    }
    if (isFire)
    {
        isFire = false;
        return FIRE_STATE_ID;
    }
    if (isWater)
    {
        isWater = false;
        return WATER_STATE_ID;
    }
    if (isEarth)
    {
        isEarth = false;
        return EARTH_STATE_ID;
    }
    if (isAir)
    {
        isAir = false;
        return AIR_STATE_ID;
    }
    quit->update(window, deltaTime);
    return NULL_STATE_ID;
}

void STE::ClientSelection::didPress(Button* button)
{
    if (button == quit)
    {
        return;
    }
    if (button == fire)
    {
        return;
    }
    if (button == water)
    {
        return;
    }
    if (button == earth)
    {
        return;
    }
    if (button == air)
    {
        return;
    }
}

void STE::ClientSelection::didRelease(Button* button)
{
    if (button == quit)
    {
        isQuit = true;
        return;
    }
    if (button == fire)
    {
        isFire = true;
        return;
    }
    if (button == water)
    {
        isWater = true;
        return;
    }
    if (button == earth)
    {
        isEarth = true;
        return;
    }
    if (button == air)
    {
        isAir = true;
        return;
    }
}
