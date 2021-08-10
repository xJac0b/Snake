#include "pch.h"
#include "Apple.h"

Apple::Apple(sf::FloatRect&& bounds, sf::Texture& texture, float& grid_size) : Entity(bounds, texture, grid_size)
{
	gui::setVectorShape(this->sprite, sf::FloatRect(0, 192, 60, 64), 0);
}

Apple::~Apple()
{
}

void Apple::newApple()
{
	this->setPosition(sf::Vector2f(38.f + rand() % 15 * this->gridSize, 38.f + rand() % 15 * this->gridSize));
	this->updateGridPos();
}

void Apple::update(const float& dt)
{
}

void Apple::render(sf::RenderTarget& target)
{
	target.draw(&this->sprite[0], 4, sf::Quads, this->state);
}
