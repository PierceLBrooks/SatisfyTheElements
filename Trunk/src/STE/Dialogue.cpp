
// Author: Pierce Brooks

#include <STE/Dialogue.hpp>
#include <iostream>

STE::Dialogue::Dialogue(const std::string& path)
{
    std::cout << path << std::endl;
    file = new std::ifstream();
    file->open(path);
    if (!file->is_open())
    {
        std::cout << "Invalid path!" << std::endl;
        delete file;
        file = nullptr;
    }
}

STE::Dialogue::~Dialogue()
{
    delete file;
    for (unsigned int i = 0; i != options.size(); ++i)
    {
        delete options[i];
    }
    options.clear();
}

int STE::Dialogue::update(sf::RenderWindow* window, float deltaTime)
{
    if (file == nullptr)
    {
        return -1;
    }
    for (unsigned int i = 0; i != options.size(); ++i)
    {
        options[i]->update(window, deltaTime);
    }
    return 0;
}
