
// Author: Pierce Brooks

#include <STE/Entity.hpp>
#include <STE/STE.hpp>

std::map<std::string, sf::Texture*>* STE::Entity::textures = nullptr;
std::map<std::string, std::pair<sf::SoundBuffer*, sf::Sound*>>* STE::Entity::sounds = nullptr;

STE::Entity::Entity()
{

}

STE::Entity::~Entity()
{

}

sf::Texture* STE::Entity::loadTexture(const std::string& path)
{
    sf::Texture* texture = nullptr;
    if (textures == nullptr)
    {
        return texture;
    }
    std::map<std::string, sf::Texture*>::iterator iter = textures->find(path);
    if (iter != textures->end())
    {
        texture = iter->second;
    }
    else
    {
        texture = new sf::Texture();
        if (!texture->loadFromFile(path))
        {
            delete texture;
            texture = nullptr;
            return texture;
        }
        (*textures)[path] = texture;
    }
    return texture;
}

sf::Sound* STE::Entity::loadSound(const std::string& path)
{
    sf::Sound* sound = nullptr;
    if (sounds == nullptr)
    {
        return sound;
    }
    std::map<std::string, std::pair<sf::SoundBuffer*, sf::Sound*>>::iterator iter = sounds->find(path);
    if (iter != sounds->end())
    {
        sound = std::get<1>(iter->second);
    }
    else
    {
        sf::SoundBuffer* buffer = new sf::SoundBuffer();
        if (!buffer->loadFromFile(path))
        {
            delete buffer;
            return sound;
        }
        sound = new sf::Sound();
        sound->setBuffer(*buffer);
        sound->setVolume(DEFAULT_VOLUME);
        (*sounds)[path] = std::pair<sf::SoundBuffer*, sf::Sound*>(buffer, sound);
    }
    return sound;
}

void STE::Entity::load()
{
    if (textures == nullptr)
    {
        textures = new std::map<std::string, sf::Texture*>();
    }
    if (sounds == nullptr)
    {
        sounds = new std::map<std::string, std::pair<sf::SoundBuffer*, sf::Sound*>>();
    }
}

void STE::Entity::unload()
{
    if (textures != nullptr)
    {
        for (std::map<std::string, sf::Texture*>::iterator iter = textures->begin(); iter != textures->end(); ++iter)
        {
            delete iter->second;
        }
        textures->clear();
        delete textures;
        textures = nullptr;
    }
    if (sounds != nullptr)
    {
        for (std::map<std::string, std::pair<sf::SoundBuffer*, sf::Sound*>>::iterator iter = sounds->begin(); iter != sounds->end(); ++iter)
        {
            delete std::get<0>(iter->second);
            delete std::get<1>(iter->second);
        }
        sounds->clear();
        delete sounds;
        sounds = nullptr;
    }
}
