
// Author: Pierce Brooks

#include <STE/STE.hpp>
#include <STE/Button.hpp>
#include <SFML/WIndow/Mouse.hpp>

STE::Button::Listener::Listener()
{

}

STE::Button::Listener::~Listener()
{

}

STE::Button::Button(const sf::Vector2f& region, const std::string& content, sf::Font* font, const sf::Color& color, bool center) :
    Entity(),
    region(region),
    isPressed(false),
    listener(nullptr),
    action(nullptr),
    center(center)
{
    form = new sf::RectangleShape();
    form->setSize(region);
    form->setOrigin(region*0.5f);

    label = new sf::Text();
    label->setFont(*font);
    label->setString(sf::String(content));
    label->setFillColor(color);
    bounds = label->getLocalBounds();
}

STE::Button::~Button()
{
    delete action;
}

int STE::Button::update(sf::RenderWindow* window, float deltaTime)
{
    bool released = false;
    bool hover = false;
    sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(*window));
    if (form->getGlobalBounds().contains(mouse))
    {
        hover = true;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            if (!isPressed)
            {
                press();
            }
        }
        else
        {
            if (isPressed)
            {
                release();
                released = true;
            }
        }
    }
    else
    {
        if (isPressed)
        {
            isPressed = false;
        }
    }
    reset();
    window->draw(*form);
    window->draw(*label);
    if (released)
    {
        return -1;
    }
    if (hover)
    {
        return 1;
    }
    return 0;
}

bool STE::Button::getIsPressed() const
{
    return isPressed;
}

void STE::Button::setListener(Listener* listener)
{
    this->listener = listener;
}

void STE::Button::setAction(Action* action)
{
    this->action = action;
}

void STE::Button::reset()
{
    form->setPosition(getPosition());
    form->setRotation(getRotation());
    form->setScale(getScale());

    label->setPosition(getPosition());
    label->setRotation(getRotation());
    label->setOrigin(sf::Vector2f(bounds.width, bounds.height));
    label->setScale(sf::Vector2f((region.x/bounds.width)*1.5f, region.y/bounds.height)*0.5f);
    label->move(label->getGlobalBounds().width*0.5f, 0.0f);

    if (!isPressed)
    {
        form->setFillColor(BUTTON_RELEASED_COLOR);
    }
    else
    {
        form->setFillColor(BUTTON_PRESSED_COLOR);
    }

    if (!center)
    {
        form->move(form->getOrigin());
        label->move(form->getOrigin());
    }
}

void STE::Button::press()
{
    isPressed = true;
    if (listener != nullptr)
    {
        listener->didPress(this);
    }
    if (action != nullptr)
    {
        (*action)(this, true);
    }
}

void STE::Button::release()
{
    isPressed = false;
    if (listener != nullptr)
    {
        listener->didRelease(this);
    }
        if (action != nullptr)
    {
        (*action)(this, false);
    }
}
