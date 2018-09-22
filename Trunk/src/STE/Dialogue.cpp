
// Author: Pierce Brooks

#include <STE/Dialogue.hpp>
#include <iostream>

STE::Dialogue::Dialogue(const std::string& path)
{
    std::string line;
    std::cout << path << std::endl;
    file = new std::ifstream();
    file->open(path);
    if (!file->is_open())
    {
        std::cout << "Invalid path!" << std::endl;
        delete file;
        file = nullptr;
    }
    else
    {
        while (std::getline(*file, line).good())
        {
            std::cout << line << std::endl;
            lines.push_back(line);
        }
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
    lines.clear();
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
