#include "pch.h"
#include "Entity.h"

Entity::Entity(sf::FloatRect& bounds, sf::Texture& texture, float& grid_size) : texture(texture), gridSize(grid_size)
{
	this->sprite.resize(4, sf::Vertex());
	gui::setVectorShape(this->sprite, bounds);
	this->state.texture = &texture;
	this->updateGridPos();
}

Entity::~Entity()
{
}

const sf::FloatRect& Entity::getBounds()
{
	return gui::getVectorShape(this->sprite);
}

const sf::Vector2i& Entity::getGridPos() const
{
	return this->gridPosition;
}

const sf::Vector2f& Entity::getPosition() const
{
	return this->sprite[0].position;
}

void Entity::setPosition(sf::Vector2f&& pos)
{
	gui::setVectorShape(this->sprite, sf::FloatRect(pos, sf::Vector2f(gui::getVectorShape(this->sprite).width,
		gui::getVectorShape(this->sprite).height)));
}

void Entity::updateGridPos()
{
	this->gridPosition = sf::Vector2i((static_cast<int>(this->getPosition().x) - 26) / this->gridSize, (static_cast<int>(this->getPosition().y) - 15) / this->gridSize);
}

