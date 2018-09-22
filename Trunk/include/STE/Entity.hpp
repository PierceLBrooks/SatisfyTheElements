
// Author: Pierce Brooks

#ifndef STE_ENTITY_HPP
#define STE_ENTITY_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <map>

namespace STE
{
    class Entity
    {
    public:
        Entity();
        ~Entity();
        virtual int update(sf::RenderWindow* window, float deltaTime) = 0;
        static sf::Texture* loadTexture(const std::string& path);
        static void unloadTextures();
    private:
        static std::map<std::string, sf::Texture*> textures;
    };
}

#endif // STE_ENTITY_HPP

