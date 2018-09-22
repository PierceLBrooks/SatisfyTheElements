
// Author: Pierce Brooks

#include <STE/Menu.hpp>

STE::Menu::Menu(sf::RenderWindow* window, unsigned int cherryBlossomsSegmentation) :
    State(MENU_STATE_ID)
{
    float segmentation = sf::Vector2f(window->getSize()).x/static_cast<float>(cherryBlossomsSegmentation);
    for (unsigned int i = 0; i != cherryBlossomsSegmentation; ++i)
    {
        cherryBlossoms.push_back(new CherryBlossoms(segmentation*static_cast<float>(i)));
    }
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
    for (unsigned int i = 0; i != cherryBlossoms.size(); ++i)
    {
        CherryBlossoms* cb = cherryBlossoms[i];
        cb->update(window, deltaTime);
    }
    return 0;
}
