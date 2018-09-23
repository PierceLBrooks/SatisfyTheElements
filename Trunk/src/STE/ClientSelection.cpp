
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
    float offset = region.y*0.125f;
    quit = new Button(region*BUTTON_SCALE, "Quit", getFont(), DEFAULT_TEXT_COLOR, false);
    quit->setListener(this);
    fire = new Button(region*BUTTON_SCALE, "Fire", getFont(), DEFAULT_TEXT_COLOR, false);
    fire->setListener(this);
    water = new Button(region*BUTTON_SCALE, "Water", getFont(), DEFAULT_TEXT_COLOR, false);
    water->setListener(this);
    earth = new Button(region*BUTTON_SCALE, "Earth", getFont(), DEFAULT_TEXT_COLOR, false);
    earth->setListener(this);
    air = new Button(region*BUTTON_SCALE, "Air", getFont(), DEFAULT_TEXT_COLOR, false);
    air->setListener(this);
    fire->setPosition(region*0.5f);
    fire->move(-offset, (region.y*BUTTON_SCALE)+offset);
    water->setPosition(region*0.5f);
    water->move(-offset, ((region.y*BUTTON_SCALE)+offset)*-1.0f);
    earth->setPosition(region*0.5f);
    earth->move(offset, (region.y*BUTTON_SCALE)+offset);
    air->setPosition(region*0.5f);
    air->move(offset, ((region.y*BUTTON_SCALE)+offset)*-1.0f);
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
    mouse();
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
    fire->update(window, deltaTime);
    water->update(window, deltaTime);
    earth->update(window, deltaTime);
    air->update(window, deltaTime);
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
