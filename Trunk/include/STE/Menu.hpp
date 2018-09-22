
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
    private:
        std::vector<CherryBlossoms*> cherryBlossoms;
    };
}

#endif // STE_MENU_HPP
