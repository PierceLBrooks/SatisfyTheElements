
// Author: Pierce Brooks

#ifndef STE_DATE_HPP
#define STE_DATE_HPP

#include <STE/State.hpp>

namespace STE
{
    class Date : public State
    {
    public:
        Date(sf::RenderWindow* window);
        ~Date();
        int update(sf::RenderWindow* window, float deltaTime);
    private:
        Button* quit;
    };
}

#endif // STE_DATE_HPP
