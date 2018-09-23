
// Author: Pierce Brooks

#include <STE/Dialogue.hpp>
#include <iostream>
#include <cstdlib>

std::map<std::string, int>* STE::Dialogue::emotions = nullptr;
std::map<int, std::string>* STE::Dialogue::emotionPaths = nullptr;
std::map<int, std::string>* STE::Dialogue::characterPaths = nullptr;

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
    score(DEFAULT_SCORE),
    elementIndex(0),
    characterEmotion(nullptr)
{
    if (state == nullptr)
    {
        return;
    }
    sf::Vector2f region = sf::Vector2f(window->getSize());
    std::string backgroundPath;
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
    speech->setOutlineColor(sf::Color(255-speech->getFillColor().r, 255-speech->getFillColor().g, 255-speech->getFillColor().b, speech->getFillColor().a));
    speech->setOutlineThickness(static_cast<float>(speech->getCharacterSize())*TEXT_OUTLINE_THICKNESS*0.5f);
    speech->setPosition(region.x*0.5f, region.y);
    speech->setString(sf::String(""));
    speech->setCharacterSize(static_cast<int>(static_cast<float>(speech->getCharacterSize())*0.75f));
    switch (state->getID())
    {
    case FIRE_STATE_ID:
        backgroundPath = "mall";
        break;
    case WATER_STATE_ID:
        backgroundPath = "park";
        break;
    case EARTH_STATE_ID:
        backgroundPath = "coffee";
        break;
    case AIR_STATE_ID:
        backgroundPath = "concert";
        break;
    default:
        backgroundPath = "";
        break;
    }
    if (backgroundPath.empty())
    {
        background = nullptr;
    }
    else
    {
        background = new sf::Sprite();
        background->setTexture(*loadTexture("./Assets/Images/Backgrounds/"+backgroundPath+".png"));
        background->setOrigin(sf::Vector2f(background->getTexture()->getSize())*0.5f);
    }
}

STE::Dialogue::~Dialogue()
{
    delete characterEmotion;
    delete background;
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

void STE::Dialogue::reset()
{
    score = DEFAULT_SCORE;
    elementIndex = 0;
}

void STE::Dialogue::finish()
{
    delete characterEmotion;
    characterEmotion = nullptr;
    if (speech == nullptr)
    {
        return;
    }
    speech->setString(sf::String(""));
}

int STE::Dialogue::update(sf::RenderWindow* window, float deltaTime)
{
    sf::Vector2f region = sf::Vector2f(window->getSize());
    if (background != nullptr)
    {
        background->setPosition(region*0.5f);
        background->setScale(region.x/static_cast<float>(background->getTexture()->getSize().x), region.y/static_cast<float>(background->getTexture()->getSize().y));
        window->draw(*background);
    }
    if (characterEmotion != nullptr)
    {
        characterEmotion->setScale(region.y/static_cast<float>(characterEmotion->getTexture()->getSize().y), region.y/static_cast<float>(characterEmotion->getTexture()->getSize().y));
        characterEmotion->setPosition(region.x*0.5f, region.y);
        window->draw(*characterEmotion);
    }
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

std::string STE::Dialogue::getEmotionPath(int emotion)
{
    if (emotionPaths == nullptr)
    {
        return "";
    }
    std::map<int, std::string>::iterator iter = emotionPaths->find(emotion);
    if (iter != emotionPaths->end())
    {
        return iter->second;
    }
    return "";
}

std::string STE::Dialogue::getCharacterPath(int character)
{
    if (characterPaths == nullptr)
    {
        return "";
    }
    std::map<int, std::string>::iterator iter = characterPaths->find(character);
    if (iter != characterPaths->end())
    {
        return iter->second;
    }
    return "";
}

void STE::Dialogue::load()
{
    if (emotions == nullptr)
    {
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
    if (emotionPaths == nullptr)
    {
        emotionPaths = new std::map<int, std::string>();
        (*emotionPaths)[1] = "smile";
        (*emotionPaths)[2] = "happy";
        (*emotionPaths)[3] = "anger";
        (*emotionPaths)[4] = "grossed";
        (*emotionPaths)[5] = "blushing";
        (*emotionPaths)[6] = "surprise";
        for (std::map<int, std::string>::iterator iter = emotionPaths->begin(); iter != emotionPaths->end(); ++iter)
        {
            iter->second = "-"+iter->second;
        }
    }
    if (characterPaths == nullptr)
    {
        characterPaths = new std::map<int, std::string>();
        (*characterPaths)[1] = "Fire/fire";
        (*characterPaths)[2] = "Water/water";
        (*characterPaths)[3] = "Earth/earth";
        (*characterPaths)[4] = "Air/air";
        for (std::map<int, std::string>::iterator iter = characterPaths->begin(); iter != characterPaths->end(); ++iter)
        {
            iter->second = "./Assets/Images/Elementals/"+iter->second;
        }
    }
}

void STE::Dialogue::unload()
{
    if (emotions != nullptr)
    {
        emotions->clear();
        delete emotions;
        emotions = nullptr;
    }
    if (emotionPaths != nullptr)
    {
        emotionPaths->clear();
        delete emotionPaths;
        emotionPaths = nullptr;
    }
    if (characterPaths != nullptr)
    {
        characterPaths->clear();
        delete characterPaths;
        characterPaths = nullptr;
    }
}

void STE::Dialogue::parse(const sf::Vector2f& region, State* state)
{
    //std::cout << "BEGIN PARSE" << std::endl;
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
            if (line.size() > MAX_LINE_LENGTH)
            {
                std::vector<std::string> split;
                unsigned int splitOffset = 0;
                unsigned int splitCount = 0;
                for (unsigned int i = 0; i < line.size(); ++i)
                {
                    ++splitCount;
                    if (splitCount > MAX_LINE_LENGTH)
                    {
                        if ((line[i] == '.') || (line[i] == '!') || (line[i] == '?'))
                        {
                            split.push_back(line.substr(splitOffset, splitCount+1));
                            ++i;
                            splitOffset = i;
                            splitCount = 0;
                        }
                    }
                }
                if (splitCount > 0)
                {
                    split.push_back(line.substr(splitOffset));
                }
                for (unsigned int i = 0; i != split.size(); ++i)
                {
                    if (split[i].empty())
                    {
                        continue;
                    }
                    for (unsigned int j = 0; j != split[i].size(); ++j)
                    {
                        if (split[i][j] != ' ')
                        {
                            elements.push_back(new Statement(character, split[i], emotion));
                            break;
                        }
                    }
                }
                split.clear();
            }
            else
            {
                elements.push_back(new Statement(character, line, emotion));
            }
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

void STE::Dialogue::show(int character, int emotion)
{
    std::string characterPath = getCharacterPath(character);
    std::string emotionPath = getEmotionPath(emotion);
    if ((characterPath.empty()) || (emotionPath.empty()))
    {
        return;
    }
    sf::Vector2f region;
    std::string path = characterPath+emotionPath+".png";
    if (characterEmotion == nullptr)
    {
        characterEmotion = new sf::Sprite();
    }
    characterEmotion->setTexture(*loadTexture(path));
    region = sf::Vector2f(characterEmotion->getTexture()->getSize());
    characterEmotion->setOrigin(region.x*0.5f, region.y);
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
    show(statement->getCharacter(), statement->getEmotion());
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

