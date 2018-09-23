
// Author: Pierce Brooks

#include <map>
#include <iostream>
#include <STE/STE.hpp>
#include <STE/State.hpp>
#include <STE/Menu.hpp>
#include <STE/Intro.hpp>
#include <STE/ClientSelection.hpp>
#include <STE/Date.hpp>
#include <STE/Result.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

void load()
{
    STE::Date::loadDates();
    STE::Entity::loadTextures();
    STE::Dialogue::loadEmotions();
}

void unload()
{
    STE::Date::unloadDates();
    STE::Entity::unloadTextures();
    STE::Dialogue::unloadEmotions();
}

int handleState(sf::RenderWindow* window, float deltaTime, int state, std::map<int, STE::State*>& states)
{
    int stateNext = NULL_STATE_ID;
    if (state > NULL_STATE_ID)
    {
        std::map<int, STE::State*>::iterator iter = states.find(state);
        if (iter != states.end())
        {
            STE::State* stateCurrent = iter->second;
            stateNext = stateCurrent->update(window, deltaTime);
        }
    }
    return stateNext;
}

int main()
{
    unsigned int shadowFrames;
    float shadowFrameTime;
    float deltaTime;
    int state = MENU_STATE_ID;
    int stateNext = INVALID_STATE_ID;
    int statePrevious = INVALID_STATE_ID;
    std::map<int, STE::State*> states;
    sf::Event event;
    sf::Color background = sf::Color(152, 152, 152);
    sf::Clock* clock = new sf::Clock();
    sf::Font* font = new sf::Font();
    sf::Text* fps = new sf::Text();
    sf::RenderWindow* window = new sf::RenderWindow();
    auto videoModes = sf::VideoMode::getFullscreenModes();
    // ^ hey C&D, check that one out lol
    window->create(videoModes[videoModes.size()/2], "Satisfy the Elements", sf::Style::Default);
    window->setFramerateLimit(FPS_LIMIT);
    load();
    states[MENU_STATE_ID] = new STE::Menu(window, 10);
    states[INTRO_STATE_ID] = new STE::Intro(window);
    states[CLIENT_SELECTION_STATE_ID] = new STE::ClientSelection(window);
    states[FIRE_STATE_ID] = new STE::Date(window, FIRE_STATE_ID);
    states[WATER_STATE_ID] = new STE::Date(window, WATER_STATE_ID);
    states[EARTH_STATE_ID] = new STE::Date(window, EARTH_STATE_ID);
    states[AIR_STATE_ID] = new STE::Date(window, AIR_STATE_ID);
    states[RESULT_STATE_ID] = new STE::Result(window, RESULT_STATE_ID);
    clock->restart();
    if (!font->loadFromFile("./Assets/Fonts/Arial/arial.ttf"))
    {
        delete clock;
        delete font;
        delete fps;
        delete window;
        return -1;
    }
    fps->setFont(*font);
    fps->setFillColor(DEFAULT_TEXT_COLOR);
    fps->setString(sf::String("FPS"));
    while (window->isOpen())
    {
        while (window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::EventType::Closed:
                window->close();
                break;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        {
            window->close();
            continue;
        }
        window->clear(background);
        deltaTime = clock->restart().asSeconds();
        if (deltaTime > MAX_DELTA_TIME)
        {
            shadowFrames = 1;
            do
            {
                ++shadowFrames;
                shadowFrameTime = deltaTime/static_cast<float>(shadowFrames);
            } while (shadowFrameTime > MAX_DELTA_TIME);
            for (unsigned int i = 0; i != shadowFrames; ++i)
            {
                handleState(window, shadowFrameTime, state, states);
            }
        }
        else
        {
            stateNext = handleState(window, deltaTime, state, states);
            if (stateNext < NULL_STATE_ID)
            {
                window->close();
                continue;
            }
            if (stateNext != NULL_STATE_ID)
            {
                std::map<int, STE::State*>::iterator iter = states.find(stateNext);
                statePrevious = state;
                state = stateNext;
                std::cout << state << std::endl;
                if (iter != states.end())
                {
                    iter->second->start();
                }
            }
        }
        fps->setString(sf::String(std::to_string(static_cast<int>(1.0f/deltaTime))));
        fps->setPosition(static_cast<float>(window->getSize().x), 0.0f);
        fps->move((fps->getPosition()-fps->findCharacterPos(fps->getString().getSize()-1))*2.0f);
        window->draw(*fps);
        window->display();
    }
    delete clock;
    delete font;
    delete fps;
    delete window;
    unload();
    for (std::map<int, STE::State*>::iterator iter = states.begin(); iter != states.end(); ++iter)
    {
        delete iter->second;
    }
    states.clear();
    return 0;
}
