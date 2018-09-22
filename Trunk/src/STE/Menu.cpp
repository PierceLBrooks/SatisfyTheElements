
// Author: Pierce Brooks

#include <STE/Menu.hpp>

STE::Menu::Menu(sf::RenderWindow* window, unsigned int cherryBlossomsSegmentation) :
    State(MENU_STATE_ID),
    isQuit(false)
{
    sf::Vector2f region = sf::Vector2f(window->getSize());
    float segmentation = region.x/static_cast<float>(cherryBlossomsSegmentation);
    float offset = segmentation*0.5f;
    for (unsigned int i = 0; i != cherryBlossomsSegmentation; ++i)
    {
        cherryBlossoms.push_back(new CherryBlossoms(offset+(segmentation*static_cast<float>(i))));
    }
    font = new sf::Font();
    font->loadFromFile("./Assets/Fonts/Tangerine/Tangerine_Bold.ttf");
    quit = new Button(region*0.125f, "Quit", font, sf::Color::Green);
    quit->setListener(this);
    quit->setPosition(region*0.5f);
}

STE::Menu::~Menu()
{
    for (unsigned int i = 0; i != cherryBlossoms.size(); ++i)
    {
        delete cherryBlossoms[i];
    }
    cherryBlossoms.clear();
}

int STE::Menu::update(sf::RenderWindow* window, float deltaTime)
{
    if (isQuit)
    {
        return INVALID_STATE_ID;
    }
    for (unsigned int i = 0; i != cherryBlossoms.size(); ++i)
    {
        CherryBlossoms* cb = cherryBlossoms[i];
        cb->update(window, deltaTime);
    }
    quit->update(window, deltaTime);
    return NULL_STATE_ID;
}

void STE::Menu::didPress(Button* button)
{
    if (button == quit)
    {
        return;
    }
}

void STE::Menu::didRelease(Button* button)
{
    if (button == quit)
    {
        isQuit = true;
        return;
    }
}
