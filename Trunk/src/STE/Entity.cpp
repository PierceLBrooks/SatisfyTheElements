
// Author: Pierce Brooks

#include <STE/Entity.hpp>

std::map<std::string, sf::Texture*> STE::Entity::textures = std::map<std::string, sf::Texture*>();

STE::Entity::Entity()
{

}

STE::Entity::~Entity()
{

}

sf::Texture* STE::Entity::loadTexture(const std::string& path)
{
    sf::Texture* texture = nullptr;
    std::map<std::string, sf::Texture*>::iterator iter = textures.find(path);
    if (iter != textures.end())
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
        textures[path] = texture;
    }
    return texture;
}

void STE::Entity::unloadTextures()
{
    for (std::map<std::string, sf::Texture*>::iterator iter = textures.begin(); iter != textures.end(); ++iter)
    {
        delete iter->second;
    }
    textures.clear();
}
