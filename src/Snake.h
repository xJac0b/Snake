#pragma once
#include "Apple.h"

class SnakePart : public Entity
{
public:
    SnakePart(sf::FloatRect&& bounds, sf::Texture& texture, sf::Vector2f dir, float& gridSize);
    ~SnakePart();

    void setTurn(short x = 0);
    short& getTurn();
    sf::Vector2f& getDir();
    std::vector<sf::Vertex>& getVArray();
    void update(const float& dt);
    void render(sf::RenderTarget& target);
private:
    sf::Vector2f dir;
    short turn; // 0 - no, 1...4 - turns
};

class Snake :
    public Entity
{
public:
    Snake(sf::FloatRect&& bounds, sf::Texture& texture, float& grid_size);
    ~Snake();
    
    const bool touchTail() const;
    const std::vector<SnakePart>& getTail() const;
    void move();
    void grow();
    void update(const float& dt);
    void render(sf::RenderTarget& target);
private:
    sf::Vector2f logDirBack;
    std::vector<SnakePart> tail;
    std::unique_ptr<Keytime> keyTime, snakeTime;
    char key;
    sf::Vector2f dir; //  x:-1 -  left, 1 -  left
    // y: -1 - top, 1 - down
};

