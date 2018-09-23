
// Author: Pierce Brooks

#ifndef STE_RESULT_HPP
#define STE_RESULT_HPP

#include <STE/State.hpp>
#include <STE/Button.hpp>

namespace STE
{
    class Result : public State
    {
    public:
        Result(sf::RenderWindow* window, int id);
        ~Result();
        int update(sf::RenderWindow* window, float deltaTime);
        void start();
        static void setIsWin(bool isWin);
    private:
        static bool isWin;
        bool isQuit;
        Button* finish;
    };
}

#endif // STE_RESULT_HPP
