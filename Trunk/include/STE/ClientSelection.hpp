
// Author: Pierce Brooks

#ifndef STE_CLIENT_SELECTION_HPP
#define STE_CLIENT_SELECTION_HPP

#include <STE/State.hpp>

namespace STE
{
    class ClientSelection : public State
    {
    public:
        ClientSelection(sf::RenderWindow* window);
        ~ClientSelection();
        int update(sf::RenderWindow* window, float deltaTime);
    protected:
        void didPress(Button* button);
        void didRelease(Button* button);
    private:
        bool isQuit;
        bool isFire;
        bool isWater;
        bool isEarth;
        bool isAir;
        Button* quit;
        Button* fire;
        Button* water;
        Button* earth;
        Button* air;
    };
}

#endif // STE_CLIENT_SELECTION_HPP
