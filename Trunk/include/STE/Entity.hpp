
// Author: Pierce Brooks

#ifndef STE_ENTITY_HPP
#define STE_ENTITY_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
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
        static sf::Sound* loadSound(const std::string& path);
        static void load();
        static void unload();
    private:
        static std::map<std::string, sf::Texture*>* textures;
        static std::map<std::string, std::pair<sf::SoundBuffer*, sf::Sound*>>* sounds;
    };
}

#endif // STE_ENTITY_HPP

