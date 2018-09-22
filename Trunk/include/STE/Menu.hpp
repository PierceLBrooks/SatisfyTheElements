
// Author: Pierce Brooks

#ifndef STE_MENU_HPP
#define STE_MENU_HPP

#include <STE/State.hpp>
#include <STE/Button.hpp>
#include <STE/CherryBlossoms.hpp>
#include <SFML/Graphics/Font.hpp>
#include <vector>

namespace STE
{
    class Menu : public State, public Button::Listener
    {
    public:
        Menu(sf::RenderWindow* window, unsigned int cherryBlossomsSegmentation);
        ~Menu();
        int update(sf::RenderWindow* window, float deltaTime);
    private:
        std::vector<CherryBlossoms*> cherryBlossoms;
        sf::Font* font;
        Button* quit;
        bool isQuit;
    protected:
        void didPress(Button* button);
        void didRelease(Button* button);
    };
}

#endif // STE_MENU_HPP
