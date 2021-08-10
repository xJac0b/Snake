#pragma once
#include "Entity.h"
class Apple :
    public Entity
{
public:
    Apple(sf::FloatRect&& bounds, sf::Texture& texture, float& grid_size);
    ~Apple();

    void newApple();
    void update(const float& dt);
    void render(sf::RenderTarget& target);
};

