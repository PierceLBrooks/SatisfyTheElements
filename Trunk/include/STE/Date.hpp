
// Author: Pierce Brooks

#ifndef STE_DATE_HPP
#define STE_DATE_HPP

#include <STE/State.hpp>
#include <STE/Dialogue.hpp>

namespace STE
{
    class Date : public State
    {
    public:
        Date(sf::RenderWindow* window, int type);
        ~Date();
        int update(sf::RenderWindow* window, float deltaTime);
        static std::string getDate(int type);
        static void loadDates();
        static void unloadDates();
    protected:
        void didPress(Button* button);
        void didRelease(Button* button);
    private:
        static std::map<int, std::string>* dates;
        bool isQuit;
        Dialogue* dialogue;
        Button* quit;
    };
}

#endif // STE_DATE_HPP
