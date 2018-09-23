
// Author: Pierce Brooks

#ifndef STE_DIALOGUE_HPP
#define STE_DIALOGUE_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <STE/State.hpp>
#include <fstream>
#include <vector>
#include <string>
#include <map>

namespace STE
{
    class Dialogue : public Entity
    {
    public:
        Dialogue(sf::RenderWindow* window, const std::string& path, State* state);
        ~Dialogue();
        bool show();
        void reset();
        void finish();
        int update(sf::RenderWindow* window, float deltaTime);
        int getScore() const;
        static int getEmotion(const std::string& identifier);
        static std::string getEmotionPath(int emotion);
        static std::string getCharacterPath(int character);
        static void load();
        static void unload();
    private:
        class Element
        {
        public:
            Element(bool type, int character);
            ~Element();
            bool getType() const;
            int getCharacter() const;
        private:
            bool type;
            int character;
        };
        class Statement : public Element
        {
        public:
            Statement(int character, const std::string& content, int emotion = 0);
            ~Statement();
            const std::string& getContent() const;
            int getEmotion() const;
        private:
            std::string content;
            int emotion;
        };
        class Question : public Element
        {
        public:
            Question(int character);
            ~Question();
            void addOption(Button* option);
            const std::vector<Button*>& getOptions() const;
        private:
            std::vector<Button*> options;
        };
        void parse(const sf::Vector2f& region, State* state);
        bool select(Button* option);
        void show(int character, int emotion);
        void show(const std::vector<Statement*>& statements);
        void show(Statement* statement);
        void ask(Question* question);
        std::vector<std::string> lines;
        std::vector<Button*> options;
        std::vector<Element*> elements;
        std::vector<Statement*> statements;
        std::map<Button*, std::vector<Statement*>> responses;
        std::ifstream* file;
        sf::Sprite* background;
        sf::Sprite* characterEmotion;
        sf::Text* speech;
        int score;
        unsigned int elementIndex;
        static std::map<std::string, int>* emotions;
        static std::map<int, std::string>* emotionPaths;
        static std::map<int, std::string>* characterPaths;
    };
}

#endif // STE_DIALOGUE_HPP
