
// Author: Pierce Brooks

#ifndef STE_STATE_HPP
#define STE_STATE_HPP

#include <STE/STE.hpp>
#include <STE/Entity.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace STE
{
    class State : public Entity
    {
    public:
        State(int id);
        virtual ~State();
        int getID() const;
        virtual int update(sf::RenderWindow* window, float deltaTime);
    private:
        int id;
    };
}

#endif // STE_STATE_HPP
