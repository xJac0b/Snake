#pragma once
#include "PauseMenu.h"
class Board
{
public:
    Board(float& gridSize, int width, int height, sf::Texture& texture, sf::Font& font);
    ~Board();

    const int& getScore() const;
    const short isTheEnd() const;
    void update(const float& dt);
    void render(sf::RenderTarget& target);
private:
    sf::SoundBuffer bufferEat;
    sf::SoundBuffer bufferLose;
    sf::SoundBuffer bufferWin;
    sf::SoundBuffer bufferCountDown;
    sf::Sound sound;
    bool lose;
    bool win;
    float gridSize; //size of grid in pixels
    unsigned int width; //count of grids
    unsigned int height; //count of grids
    sf::Texture& texture;
    std::vector<std::vector<sf::Vertex>>board;
    std::vector<sf::Vertex>background;
    std::unique_ptr<Snake> snake;
    std::unique_ptr<Apple> apple;
    int countdownInt;
    sf::Text countdown;
    sf::Clock timer;
};


class GameState :
    public State
{
public:
    GameState(StateData& state_data);
    ~GameState();
    void gameOver();
    void win();
    void updateSfmlEvents();
    void update(const float& dt);
    void render();
private:
    bool end;
    sf::RenderStates state;
    std::unique_ptr<PauseMenu>pauseMenu;
    std::map<sf::String, sf::Texture>textures;
    std::unique_ptr<Board>board;
    std::vector<sf::Vertex>background;
    std::vector<sf::Vertex>endBox;
    sf::Text text;
    sf::RenderStates endState;
    
};

