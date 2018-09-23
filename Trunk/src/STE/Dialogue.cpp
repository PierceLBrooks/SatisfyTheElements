
// Author: Pierce Brooks

#include <STE/Dialogue.hpp>
#include <iostream>
#include <cstdlib>

std::map<std::string, int>* STE::Dialogue::emotions = nullptr;

STE::Dialogue::Element::Element(bool type, int character) :
    type(type),
    character(character)
{

}

STE::Dialogue::Element::~Element()
{

}

bool STE::Dialogue::Element::getType() const
{
    return type;
}

int STE::Dialogue::Element::getCharacter() const
{
    return character;
}

STE::Dialogue::Statement::Statement(int character, const std::string& content, int emotion) :
    Element(true, character),
    content(content),
    emotion(emotion)
{
    if (emotion < 0)
    {
        std::cout << "Invalid emotion! (" << emotion << ")" << std::endl;
        std::cout << "\t" << content << std::endl;
    }
    else
    {
        std::cout << "New statement: " << content << " (" << character << ", " << emotion << ")" << std::endl;
    }
}

STE::Dialogue::Statement::~Statement()
{

}

const std::string& STE::Dialogue::Statement::getContent() const
{
    return content;
}

int STE::Dialogue::Statement::getEmotion() const
{
    return emotion;
}

STE::Dialogue::Question::Question(int character) :
    Element(false, character)
{

}

STE::Dialogue::Question::~Question()
{
    for (unsigned int i = 0; i != options.size(); ++i)
    {
        delete options[i];
    }
    options.clear();
}

const std::vector<STE::Button*>& STE::Dialogue::Question::getOptions() const
{
    return options;
}

void STE::Dialogue::Question::addOption(Button* option)
{
    if (option == nullptr)
    {
        return;
    }
    options.push_back(option);
}

STE::Dialogue::Dialogue(sf::RenderWindow* window, const std::string& path, State* state) :
    score(0),
    elementIndex(0)
{
    sf::Vector2f region = sf::Vector2f(window->getSize());
    std::string line;
    std::cout << path << std::endl;
    file = new std::ifstream();
    file->open(path);
    if (!file->is_open())
    {
        std::cout << "Invalid path!" << std::endl;
    }
    else
    {
        while (std::getline(*file, line).good())
        {
            //std::cout << line << std::endl;
            lines.push_back(line);
        }
        parse(region, state);
        file->close();
    }
    delete file;
    file = nullptr;
    speech = new sf::Text();
    speech->setFont(*state->getFont());
    speech->setFillColor(DEFAULT_TEXT_COLOR);
    speech->setPosition(region.x*0.5f, region.y);
    speech->setString(sf::String(""));
    speech->setCharacterSize(static_cast<int>(static_cast<float>(speech->getCharacterSize())*0.75f));
}

STE::Dialogue::~Dialogue()
{
    delete file;
    for (unsigned int i = 0; i != elements.size(); ++i)
    {
        delete elements[i];
    }
    elements.clear();
    for (std::map<Button*, std::vector<Statement*>>::iterator iter = responses.begin(); iter != responses.end(); ++iter)
    {
        std::vector<Statement*>& statements = iter->second;
        for (unsigned int i = 0; i != statements.size(); ++i)
        {
            delete statements[i];
        }
        statements.clear();
    }
    responses.clear();
    options.clear();
    lines.clear();
    statements.clear();
    delete speech;
}

int STE::Dialogue::update(sf::RenderWindow* window, float deltaTime)
{
    if (speech != nullptr)
    {
        if (speech->getString().getSize() != 0)
        {
            window->draw(*speech);
        }
    }
    for (unsigned int i = 0; i != options.size(); ++i)
    {
        if (options[i]->update(window, deltaTime) < 0)
        {
            std::cout << "Score: " << score << std::endl;
            break;
        }
    }
    return 0;
}

void STE::Dialogue::setScore(int score)
{
    this->score = score;
}

int STE::Dialogue::getScore() const
{
    return score;
}

int STE::Dialogue::getEmotion(const std::string& identifier)
{
    //std::cout << "getEmotion -> \"" << identifier << "\"" << std::endl;
    if (emotions == nullptr)
    {
        return -1;
    }
    if (identifier.empty())
    {
        return -1;
    }
    if (identifier[0] == ' ')
    {
         for (unsigned int i = 1; i != identifier.size(); ++i)
         {
             if (identifier[i] != ' ')
             {
                return getEmotion(identifier.substr(i));
             }
         }
    }
    if (identifier[identifier.size()-1] == ' ')
    {
        for (unsigned int i = identifier.size(); --i < identifier.size();)
        {
            if (identifier[i] != ' ')
            {
                return getEmotion(identifier.substr(0, i+1));
            }
        }
    }
    std::map<std::string, int>::iterator iter = emotions->find(identifier);
    if (iter == emotions->end())
    {
        return -1;
    }
    return iter->second;
}

void STE::Dialogue::loadEmotions()
{
    if (emotions != nullptr)
    {
        return;
    }
    emotions = new std::map<std::string, int>();
    (*emotions)["smile"] = 1;
    (*emotions)["smiling"] = 1;
    (*emotions)["happy"] = 2;
    (*emotions)["happiness"] = 2;
    (*emotions)["anger"] = 3;
    (*emotions)["angry"] = 3;
    (*emotions)["grossed_out"] = 4;
    (*emotions)["gross_out"] = 4;
    (*emotions)["blushing"] = 5;
    (*emotions)["blush"] = 5;
    (*emotions)["surprise"] = 6;
    (*emotions)["surprised"] = 6;
}

void STE::Dialogue::unloadEmotions()
{
    if (emotions == nullptr)
    {
        return;
    }
    emotions->clear();
    delete emotions;
    emotions = nullptr;
}

void STE::Dialogue::parse(const sf::Vector2f& region, State* state)
{
    //std::cout << "BEGIN PARSE" << std::endl;
    if (state == nullptr)
    {
        return;
    }
    Question* question = nullptr;
    bool isQuestion = false;
    std::string line;
    int length = static_cast<int>(lines.size());
    int index = -1;
    int character = -1;
    int emotion = -1;
    while (++index < length)
    {
        //std::cout << index << std::endl;
        line = lines[index];
        if (!line.empty())
        {
            while ((line[line.size()-1] == '\n') || (line[line.size()-1] == '\r'))
            {
                line = line.substr(0, line.size()-1);
            }
        }
        if (line.empty())
        {
            if (isQuestion)
            {
                isQuestion = false;
                if (question != nullptr)
                {
                    elements.push_back(question);
                    question = nullptr;
                }
            }
            continue;
        }
        if (line[0] == '#')
        {
            continue;
        }
        if (line.size() == 1)
        {
            switch (line[0])
            {
            case 'p':
            case 'P':
            case 'd':
            case 'D':
                character = 0;
                break;
            case 'f':
            case 'F':
                character = 1;
                break;
            case 'w':
            case 'W':
                character = 2;
                break;
            case 'e':
            case 'E':
                character = 3;
                break;
            case 'a':
            case 'A':
                character = 4;
                break;
            default:
                character = -1;
                break;
            }
            continue;
        }
        if (line == "question")
        {
            isQuestion = true;
            continue;
        }
        //std::cout << "hi" << std::endl;
        if (isQuestion)
        {
            Button* button;
            int score = 0;
            std::string option = "";
            std::vector<Statement*> statements;
            if (question == nullptr)
            {
                question = new Question(character);
            }
            //std::cout << "BEGIN I" << std::endl;
            for (unsigned int i = 0; i != line.size(); ++i)
            {
                //std::cout << line[i] << std::endl;
                if (line[i] == '|')
                {
                    //std::cout << "BEGIN J" << std::endl;
                    for (unsigned int j = i+1; j != line.size(); ++j)
                    {
                        //std::cout << line[j] << std::endl;
                        if (line[j] == '|')
                        {
                            emotion = getEmotion(line.substr(i+1, j-(i+1)));
                            //std::cout << "BEGIN K" << std::endl;
                            for (unsigned int k = j+1; k != line.size(); ++k)
                            {
                                //std::cout << line[k] << std::endl;
                                if (line[k] == '|')
                                {
                                    unsigned int l;
                                    for (l = j+1; l != k; ++l)
                                    {
                                        if ((line[l] != ' ') && (line[l] != '+'))
                                        {
                                            option.push_back(line[l]);
                                        }
                                    }
                                    if (!option.empty())
                                    {
                                        score = atoi(option.c_str());
                                    }
                                    for (l = k+1; l != line.size(); ++l)
                                    {
                                        if (line[l] == '|')
                                        {
                                            statements.push_back(new Statement(character, line.substr(k+1, l-(k+1)), emotion));
                                            break;
                                        }
                                    }
                                    if (statements.empty())
                                    {
                                        statements.push_back(new Statement(character, line.substr(k+1), emotion));
                                    }
                                    break;
                                }
                            }
                            //std::cout << "END K" << std::endl;
                            break;
                        }
                    }
                    option = line.substr(0, i);
                    //std::cout << "END J" << std::endl;
                    break;
                }
            }
            //std::cout << "END I" << std::endl;
            if (line[line.size()-1] == '|')
            {
                while (++index < length)
                {
                    line = lines[index];
                    if (line.empty())
                    {
                        break;
                    }
                    for (unsigned int i = 0; i != line.size(); ++i)
                    {
                        if (line[i] == '|')
                        {
                            statements.push_back(new Statement(character, line.substr(i+1), getEmotion(line.substr(0,i))));
                        }
                    }
                    if (line[line.size()-1] != '|')
                    {
                        break;
                    }
                }
            }
            button = new Button(sf::Vector2f(region.x, region.y*BUTTON_SCALE), option, state->getFont(), DEFAULT_TEXT_COLOR);
            button->setAction(new Button::Action([=](Button* actor, bool isPressed){
                                                 if (button != actor)
                                                 {
                                                     std::cout << "Invalid action!";
                                                     return;
                                                 }
                                                 if (isPressed)
                                                 {
                                                     return;
                                                 }
                                                 this->select(actor);
                                                 this->score += score;
                                                 }));
            button->setPosition(region.x*0.5f, region.y*BUTTON_SCALE*2.5f);
            button->move(0.0f, region.y*BUTTON_SCALE*static_cast<float>(question->getOptions().size())*1.5f);
            question->addOption(button);
            if (responses.find(button) == responses.end())
            {
                responses[button] = statements;
            }
        }
        else
        {
            emotion = 0;
            for (unsigned int i = line.size(); --i < line.size();)
            {
                if (line[i] == '|')
                {
                    emotion = getEmotion(line.substr(i+1));
                    line = line.substr(0, i);
                }
            }
            elements.push_back(new Statement(character, line, emotion));
        }
        emotion = -1;
    }
    //std::cout << "END PARSER" << std::endl;
}

bool STE::Dialogue::select(Button* option)
{
    if (option == nullptr)
    {
        return false;
    }
    for (unsigned int i = 0; i != options.size(); ++i)
    {
        if (options[i] == option)
        {
            std::map<Button*, std::vector<Statement*>>::iterator iter = responses.find(option);
            if (iter != responses.end())
            {
                options.clear();
                show(iter->second);
            }
            return true;
        }
    }
    return false;
}

void STE::Dialogue::show(const std::vector<Statement*>& statements)
{
    for (unsigned int i = 0; i != statements.size(); ++i)
    {
        this->statements.push_back(statements[i]);
    }
}

void STE::Dialogue::show(Statement* statement)
{
    if (statement == nullptr)
    {
        return;
    }
    if (speech == nullptr)
    {
        return;
    }
    sf::FloatRect region;
    speech->setString(sf::String(statement->getContent()));
    region = speech->getGlobalBounds();
    speech->setOrigin(sf::Vector2f(region.width*0.5f, region.height*2.0f));
    std::cout << statement->getContent() << std::endl;
}

bool STE::Dialogue::show()
{
    if (!options.empty())
    {
        return true;
    }
    if (statements.empty())
    {
        if (elementIndex < elements.size())
        {
            Element* element = elements[elementIndex];
            if (element != nullptr)
            {
                if (element->getType())
                {
                    show(static_cast<Statement*>(element));
                }
                else
                {
                    ask(static_cast<Question*>(element));
                }
            }
            ++elementIndex;
        }
        else
        {
            speech->setString(sf::String(""));
            elementIndex = 0;
            return false;
        }
    }
    else
    {
        Statement* statement = *(statements.begin());
        statements.erase(statements.begin());
        show(statement);
    }
    return true;
}

void STE::Dialogue::ask(Question* question)
{
    if (question == nullptr)
    {
        return;
    }
    options = question->getOptions();
    if (speech == nullptr)
    {
        return;
    }
    speech->setString(sf::String(""));
}

