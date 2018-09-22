
// Author: Pierce Brooks

#include <STE/CherryBlossoms.hpp>
#include <STE/STE.hpp>
#include <cmath>

STE::CherryBlossoms::CherryBlossom::CherryBlossom(float x, float rotation, float rotationSpeed, float speed, float direction) :
    Entity(),
    rotationSpeed(rotationSpeed),
    speed(speed),
    direction(direction),
    time(0.0f)
{
    sprite = new sf::Sprite();
    sprite->setTexture(*loadTexture("./Assets/Images/CherryBlossom.png"));
    sprite->setRotation(rotation);
    sprite->setOrigin(sf::Vector2f(sprite->getTexture()->getSize())*0.5f);
    sprite->setPosition(x, 0.0f);
}

STE::CherryBlossoms::CherryBlossom::~CherryBlossom()
{
    delete sprite;
}

int STE::CherryBlossoms::CherryBlossom::update(sf::RenderWindow* window, float deltaTime)
{
    deltaTime *= 0.25f;
    time += deltaTime;
    if (time >= CHERRY_BLOSSOMS_LIFE)
    {
        return -1;
    }
    sprite->rotate(rotationSpeed*deltaTime);
    sprite->move(sf::Vector2f(cosf(direction), -sinf(direction))*speed*deltaTime);
    sprite->setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>((1.0f-(time/CHERRY_BLOSSOMS_LIFE))*255.0f)));
    window->draw(*sprite);
    return 0;
}

STE::CherryBlossoms::CherryBlossoms(float x) :
    Entity(),
    x(x)
{
    time = CHERRY_BLOSSOMS_SPAWN_TIME;
}

STE::CherryBlossoms::~CherryBlossoms()
{
    for (unsigned int i = 0; i != cherryBlossoms.size(); ++i)
    {
        delete cherryBlossoms[i];
    }
    cherryBlossoms.clear();
}

int STE::CherryBlossoms::update(sf::RenderWindow* window, float deltaTime)
{
    time -= deltaTime;
    if (time <= 0.0f)
    {
        time = CHERRY_BLOSSOMS_SPAWN_TIME;
        cherryBlossoms.push_back(new CherryBlossom(x, (x/static_cast<float>(window->getSize().x))*PI*RAD_TO_DEG, CHERRY_BLOSSOMS_ROTATION_SPEED*DEG_TO_RAD, CHERRY_BLOSSOMS_SPEED, PI*1.5f));
    }
    for (int i = 0; i != cherryBlossoms.size(); ++i)
    {
        if (cherryBlossoms[i]->update(window, deltaTime) != 0)
        {
            cherryBlossoms.erase(cherryBlossoms.begin()+i);
            --i;
            continue;
        }
    }
    return 0;
}
