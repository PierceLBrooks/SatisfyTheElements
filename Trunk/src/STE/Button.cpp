
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
    label->setOutlineColor(sf::Color(255-label->getFillColor().r, 255-label->getFillColor().g, 255-label->getFillColor().b, label->getFillColor().a));
    label->setOutlineThickness(static_cast<float>(label->getCharacterSize())*TEXT_OUTLINE_THICKNESS*0.5f);
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
    if (isPressed)
    {
        form->setFillColor(BUTTON_PRESSED_COLOR);
    }
    else
    {
        if (hover)
        {
            if (form->getFillColor() == BUTTON_RELEASED_COLOR)
            {
                loadSound("./Assets/Sounds/Effects/nenadsimic_menu-selection-click.wav")->play();
            }
            form->setFillColor(sf::Color(static_cast<sf::Uint8>((static_cast<float>(BUTTON_PRESSED_COLOR.r)+static_cast<float>(BUTTON_RELEASED_COLOR.r))*0.5f),
                                         static_cast<sf::Uint8>((static_cast<float>(BUTTON_PRESSED_COLOR.g)+static_cast<float>(BUTTON_RELEASED_COLOR.g))*0.5f),
                                         static_cast<sf::Uint8>((static_cast<float>(BUTTON_PRESSED_COLOR.b)+static_cast<float>(BUTTON_RELEASED_COLOR.b))*0.5f),
                                         static_cast<sf::Uint8>((static_cast<float>(BUTTON_PRESSED_COLOR.a)+static_cast<float>(BUTTON_RELEASED_COLOR.a))*0.5f)));
        }
        else
        {
            form->setFillColor(BUTTON_RELEASED_COLOR);
        }
    }
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

void STE::Button::setLabel(const std::string& label)
{
    this->label->setString(sf::String(label));
    this->bounds = this->label->getLocalBounds();
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

    if (!center)
    {
        form->move(form->getOrigin());
        label->move(form->getOrigin());
    }
}

void STE::Button::press()
{
    if (!isPressed)
    {
        loadSound("./Assets/Sounds/Effects/inspectorj_ui-confirmation-alert-a4.wav")->play();
    }
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
