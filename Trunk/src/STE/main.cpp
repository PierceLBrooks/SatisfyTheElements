
// Author: Pierce Brooks

#include <STE/Menu.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

int main()
{
    sf::RenderWindow* window = new sf::RenderWindow();
    auto videoModes = sf::VideoMode::getFullscreenModes();
    // ^ hey C&D, check that one out lol
    window->create(videoModes[videoModes.size()-1], "Satisfy the Elements", sf::Style::Default);
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
    }
    delete window;
    return 0;
}
