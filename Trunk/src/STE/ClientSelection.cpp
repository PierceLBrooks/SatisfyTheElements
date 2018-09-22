
// Author: Pierce Brooks

#include <STE/ClientSelection.hpp>

STE::ClientSelection::ClientSelection(sf::RenderWindow* window) :
    State(CLIENT_SELECTION_STATE_ID)
{

}

STE::ClientSelection::~ClientSelection()
{

}

int STE::ClientSelection::update(sf::RenderWindow* window, float deltaTime)
{
    return NULL_STATE_ID;
}
