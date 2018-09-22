
// Author: Pierce Brooks

#include <STE/State.hpp>

STE::State::State(int id) :
    Entity(),
    id(id)
{

}

STE::State::~State()
{

}

int STE::State::getID() const
{
    return id;
}

int STE::State::update(sf::RenderWindow* window, float deltaTime)
{

}
