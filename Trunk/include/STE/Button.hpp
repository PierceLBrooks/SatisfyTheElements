
// Author: Pierce Brooks

#ifndef STE_BUTTON_HPP
#define STE_BUTTON_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <STE/Entity.hpp>
#include <string>

namespace STE
{
    class Button : public Entity, public sf::Transformable
    {
    public:
        class Listener
        {
        protected:
            Listener();
            ~Listener();
            friend class Button;
            virtual void didPress(Button* button) = 0;
            virtual void didRelease(Button* button) = 0;
        };
        Button(const sf::Vector2f& region, const std::string& content, sf::Font* font, const sf::Color& color);
        ~Button();
        int update(sf::RenderWindow* window, float deltaTime);
        bool getIsPressed() const;
        void setListener(Listener* listener);
    private:
        void reset();
        void press();
        void release();
        bool isPressed;
        sf::RectangleShape* form;
        sf::Text* label;
        sf::Vector2f region;
        sf::FloatRect bounds;
        Listener* listener;
    };
}

#endif // STE_BUTTON_HPP

