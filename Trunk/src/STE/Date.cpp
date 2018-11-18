
// Author: Pierce Brooks

#include <STE/Date.hpp>
#include <STE/Result.hpp>
#include <iostream>

std::map<int, std::string>* STE::Date::dates = nullptr;

STE::Date::Date(sf::RenderWindow* window, int type) :
    State(type),
    isQuit(false),
    isDone(false)
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
        dialogue = new Dialogue(window, getAssetsPath()+"Dialogue/"+date, this);
    }
    quit = new Button(region*BUTTON_SCALE, "Quit", getFont(), DEFAULT_TEXT_COLOR, false);
    quit->setListener(this);
    music = new sf::Music();
    switch (type)
    {
    case FIRE_STATE_ID:
        music->openFromFile(getAssetsPath()+"Sounds/Music/Steppin_Out.ogg");
        break;
    case WATER_STATE_ID:
        music->openFromFile(getAssetsPath()+"Sounds/Music/Danosongs_-_Great_World_-_Acoustic_Rock_Mix.ogg");
        break;
    case EARTH_STATE_ID:
        music->openFromFile(getAssetsPath()+"Sounds/Music/Danosongs_-_West_in_the_Shadows.ogg");
        break;
    case AIR_STATE_ID:
        music->openFromFile(getAssetsPath()+"Sounds/Music/Danosongs_-_Copper_Mountain.ogg");
        break;
    default:
        delete music;
        music = nullptr;
        break;
    }
    if (music != nullptr)
    {
        music->setLoop(true);
        music->setVolume(DEFAULT_VOLUME);
    }
}

STE::Date::~Date()
{
    delete quit;
    delete dialogue;
    delete music;
}

int STE::Date::update(sf::RenderWindow* window, float deltaTime)
{
    if (music == nullptr)
    {
        return INVALID_STATE_ID;
    }
    if (dialogue == nullptr)
    {
        return INVALID_STATE_ID;
    }
    if ((isQuit) && (!isDone))
    {
        isQuit = false;
        dialogue->reset();
        dialogue->finish();
        music->stop();
        return MENU_STATE_ID;
    }
    if (dialogue->update(window, deltaTime) < 0)
    {
        music->stop();
        return INVALID_STATE_ID;
    }
    if (isDone)
    {
        mouse(window);
        if (getIsReleased())
        {
            isDone = false;
            dialogue->finish();
            music->stop();
            return RESULT_STATE_ID;
        }
        return NULL_STATE_ID;
    }
    int buttons = 0;
    buttons |= quit->update(window, deltaTime);
    if (buttons == 0)
    {
        mouse(window);
        if (getIsReleased())
        {
            if (!dialogue->show())
            {
                if (dialogue->getScore() > 0)
                {
                    Result::setIsWin(true);
                }
                else
                {
                    Result::setIsWin(false);
                }
                dialogue->reset();
                isDone = true;
            }
            else
            {
                if (dialogue->getScore() <= 0)
                {
                    Result::setIsWin(false);
                    dialogue->reset();
                    isDone = true;
                }
            }
        }
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

void STE::Date::load()
{
    if (dates != nullptr)
    {
        return;
    }
    dates = new std::map<int, std::string>();
    (*dates)[FIRE_STATE_ID] = "fire_dialogue.txt";
    (*dates)[WATER_STATE_ID] = "water_dialogue.txt";
    (*dates)[EARTH_STATE_ID] = "earth_dialogue.txt";
    (*dates)[AIR_STATE_ID] = "air_dialogue.txt";
}

void STE::Date::unload()
{
    if (dates == nullptr)
    {
        return;
    }
    dates->clear();
    delete dates;
    dates = nullptr;
}

void STE::Date::start()
{
    if (music == nullptr)
    {
        return;
    }
    music->play();
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
