
// Author: Pierce Brooks

#include <STE/Date.hpp>

STE::Date::Date(sf::RenderWindow* window) :
    State(DATE_STATE_ID)
{

}

STE::Date::~Date()
{

}

int STE::Date::update(sf::RenderWindow* window, float deltaTime)
{
    return NULL_STATE_ID;
}

