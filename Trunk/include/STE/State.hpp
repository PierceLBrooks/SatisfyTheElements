
// Author: Pierce Brooks

#ifndef STE_STATE_HPP
#define STE_STATE_HPP

#include <STE/STE.hpp>
#include <STE/Entity.hpp>
#include <STE/Button.hpp>
#include <SFML/Graphics/Font.hpp>

namespace STE
{
    class State : public Entity, public Button::Listener
    {
    public:
        State(int id);
        virtual ~State();
        int getID() const;
        sf::Font* getFont() const;
        bool getIsPressed() const;
        bool getIsReleased() const;
        virtual int update(sf::RenderWindow* window, float deltaTime);
        virtual void start();
        void mouse();
    protected:
        virtual void didPress(Button* button);
        virtual void didRelease(Button* button);
    private:
        int id;
        bool isPressed;
        bool isReleased;
        sf::Font* font;
    };
}

#endif // STE_STATE_HPP
