
// Author: Pierce Brooks

#include <STE/Menu.hpp>

STE::Menu::Menu(sf::RenderWindow* window, unsigned int cherryBlossomsSegmentation) :
    State(MENU_STATE_ID),
    isQuit(false),
    isStart(false)
{
    sf::Vector2f region = sf::Vector2f(window->getSize());
    float segmentation = region.x/static_cast<float>(cherryBlossomsSegmentation);
    float offset = segmentation*0.5f;
    for (unsigned int i = 0; i != cherryBlossomsSegmentation; ++i)
    {
        cherryBlossoms.push_back(new CherryBlossoms(offset+(segmentation*static_cast<float>(i))));
    }
    segmentation *= 0.5f;
    quit = new Button(region*0.125f, "Quit", getFont(), DEFAULT_TEXT_COLOR);
    quit->setListener(this);
    quit->setPosition(region*0.5f);
    quit->move(0.0f, (region.y*0.125f)+segmentation);
    start = new Button(region*0.125f, "Start", getFont(), DEFAULT_TEXT_COLOR);
    start->setListener(this);
    start->setPosition(region*0.5f);
    start->move(0.0f, ((region.y*0.125f)+segmentation)*-1.0f);
}

STE::Menu::~Menu()
{
    for (unsigned int i = 0; i != cherryBlossoms.size(); ++i)
    {
        delete cherryBlossoms[i];
    }
    cherryBlossoms.clear();
    delete quit;
    delete start;
}

int STE::Menu::update(sf::RenderWindow* window, float deltaTime)
{
    mouse();
    if (isQuit)
    {
        isQuit = false;
        return INVALID_STATE_ID;
    }
    if (isStart)
    {
        isStart = false;
        return INTRO_STATE_ID;
    }
    for (unsigned int i = 0; i != cherryBlossoms.size(); ++i)
    {
        CherryBlossoms* cb = cherryBlossoms[i];
        cb->update(window, deltaTime);
    }
    quit->update(window, deltaTime);
    start->update(window, deltaTime);
    return NULL_STATE_ID;
}

void STE::Menu::didPress(Button* button)
{
    if (button == quit)
    {
        return;
    }
    if (button == start)
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
    if (button == start)
    {
        isStart = true;
        return;
    }
}
