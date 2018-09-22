
// Author: Pierce Brooks

#include <map>
#include <STE/STE.hpp>
#include <STE/State.hpp>
#include <STE/Menu.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

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
    float deltaTime;
    int state = MENU_STATE_ID;
    int stateNext = INVALID_STATE_ID;
    int statePrevious = INVALID_STATE_ID;
    std::map<int, STE::State*> states;
    sf::Clock* clock = new sf::Clock();
    sf::Font* font = new sf::Font();
    sf::Text* text = new sf::Text();
    sf::RenderWindow* window = new sf::RenderWindow();
    auto videoModes = sf::VideoMode::getFullscreenModes();
    // ^ hey C&D, check that one out lol
    window->create(videoModes[videoModes.size()-1], "Satisfy the Elements", sf::Style::Default);
    window->setFramerateLimit(60);
    states[1] = new STE::Menu(window, 10);
    clock->restart();
    if (!font->loadFromFile("./Assets/Fonts/Arial/arial.ttf"))
    {
        delete clock;
        delete font;
        delete text;
        delete window;
        return -1;
    }
    text->setFont(*font);
    text->setColor(sf::Color::Green);
    while (window->isOpen())
    {
        sf::Event event;
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
        window->clear(sf::Color::Black);
        deltaTime = clock->restart().asSeconds();
        stateNext = handleState(window, deltaTime, state, states);
        if (stateNext < NULL_STATE_ID)
        {
            continue;
        }
        if (stateNext != NULL_STATE_ID)
        {
            statePrevious = state;
            state = stateNext;
        }
        text->setString(sf::String(std::to_string(static_cast<int>(1.0f/deltaTime))));
        window->draw(*text);
        window->display();
    }
    delete window;
    delete clock;
    STE::Entity::unloadTextures();
    return 0;
}
