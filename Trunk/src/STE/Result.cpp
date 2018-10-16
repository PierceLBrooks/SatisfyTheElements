
// Author: Pierce Brooks

#include <STE/Result.hpp>
#include <iostream>

bool STE::Result::isWin = false;

STE::Result::Result(sf::RenderWindow* window, int id) :
    State(id),
    isQuit(false)
{
    sf::Vector2f region = sf::Vector2f(window->getSize());
    finish = new Button(region*BUTTON_SCALE, "", getFont(), DEFAULT_TEXT_COLOR, false);
    finish->setAction(new Button::Action([&](Button* actor, bool isPressed){
                                       if (actor != finish)
                                       {
                                           return;
                                       }
                                       if (isPressed)
                                       {
                                           return;
                                       }
                                       isQuit = true;
                                       }));
    finish->setPosition(region*0.5f);
}

STE::Result::~Result()
{
    delete finish;
}

int STE::Result::update(sf::RenderWindow* window, float deltaTime)
{
    if (isQuit)
    {
        isQuit = false;
        return CLIENT_SELECTION_STATE_ID;
    }
    finish->update(window, deltaTime);
    return NULL_STATE_ID;
}

void STE::Result::start()
{
    if (isWin)
    {
        loadSound(getAssetsPath()+"Sounds/Effects/mativve_electro-win-sound.wav")->play();
        finish->setLabel("You won!");
    }
    else
    {
        loadSound(getAssetsPath()+"Sounds/Effects/taranp_horn-fail-wahwah-3.wav")->play();
        finish->setLabel("You lose!");
    }
}

void STE::Result::setIsWin(bool isWin)
{
    Result::isWin = isWin;
}
