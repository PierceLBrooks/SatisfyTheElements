
// Author: Pierce Brooks

#ifndef STE_DIALOGUE_HPP
#define STE_DIALOGUE_HPP

#include <STE/Button.hpp>
#include <fstream>
#include <vector>
#include <string>

namespace STE
{
    class Dialogue : public Entity
    {
    public:
        Dialogue(const std::string& path);
        ~Dialogue();
        int update(sf::RenderWindow* window, float deltaTime);
    private:
        std::vector<std::string> lines;
        std::vector<Button*> options;
        std::ifstream* file;
    };
}

#endif // STE_DIALOGUE_HPP
