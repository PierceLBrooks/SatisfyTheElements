
// Author: Pierce Brooks

#ifndef STE_CHERRY_BLOSSOMS_HPP
#define STE_CHERRY_BLOSSOMS_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <STE/Entity.hpp>
#include <vector>

namespace STE
{
    class CherryBlossoms : public Entity
    {
    public:
        class CherryBlossom : public Entity
        {
        public:
            CherryBlossom(float x, float rotation, float rotationSpeed, float speed, float direction);
            ~CherryBlossom();
            int update(sf::RenderWindow* window, float deltaTime);
        private:
            float rotationSpeed;
            float speed;
            float direction;
            float time;
            sf::Sprite* sprite;
        };
        CherryBlossoms(float x);
        ~CherryBlossoms();
        int update(sf::RenderWindow* window, float deltaTime);
    private:
        std::vector<CherryBlossom*> cherryBlossoms;
        float x;
        float time;
    };
}

#endif // STE_CHERRY_BLOSSOMS_HPP

