
// Author: Pierce Brooks

#ifndef STE_MENU_HPP
#define STE_MENU_HPP

#include <STE/State.hpp>
#include <STE/CherryBlossoms.hpp>
#include <vector>

namespace STE
{
    class Menu : public State
    {
    public:
        Menu(sf::RenderWindow* window, unsigned int cherryBlossomsSegmentation);
        ~Menu();
        int update(sf::RenderWindow* window, float deltaTime);
    protected:
        void didPress(Button* button);
        void didRelease(Button* button);
    private:
        std::vector<CherryBlossoms*> cherryBlossoms;
        Button* quit;
        Button* start;
        bool isQuit;
        bool isStart;
    };
}

#endif // STE_MENU_HPP
