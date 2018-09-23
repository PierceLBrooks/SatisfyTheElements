
// Author: Pierce Brooks

#ifndef STE_DATE_HPP
#define STE_DATE_HPP

#include <STE/State.hpp>
#include <STE/Dialogue.hpp>
#include <SFML/Audio/Music.hpp>

namespace STE
{
    class Date : public State
    {
    public:
        Date(sf::RenderWindow* window, int type);
        ~Date();
        int update(sf::RenderWindow* window, float deltaTime);
        static std::string getDate(int type);
        static void load();
        static void unload();
        void start();
    protected:
        void didPress(Button* button);
        void didRelease(Button* button);
    private:
        static std::map<int, std::string>* dates;
        bool isQuit;
        bool isDone;
        Dialogue* dialogue;
        Button* quit;
        sf::Music* music;
    };
}

#endif // STE_DATE_HPP
