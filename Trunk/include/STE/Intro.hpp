
// Author: Pierce Brooks

#ifndef STE_INTRO_HPP
#define STE_INTRO_HPP

#include <STE/State.hpp>
#include <STE/Dialogue.hpp>

namespace STE
{
    class Intro : public State
    {
    public:
        Intro(sf::RenderWindow* window);
        ~Intro();
        int update(sf::RenderWindow* window, float deltaTime);
    protected:
        void didPress(Button* button);
        void didRelease(Button* button);
    private:
        Dialogue* dialogue;
        Button* quit;
        bool isQuit;
    };
}

#endif // STE_INTRO_HPP
