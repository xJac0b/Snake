#pragma once
#include "Keytime.h"
class Entity
{
public:
	Entity(sf::FloatRect& bounds, sf::Texture& texture, float& gridSize);
	~Entity();

	const sf::FloatRect& getBounds();
	const sf::Vector2i& getGridPos() const;
	const sf::Vector2f& getPosition() const;
	
	void setPosition(sf::Vector2f&& pos);
	void updateGridPos();
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target) = 0;
protected:
	float& gridSize;
	std::vector<sf::Vertex>sprite;
	sf::Texture& texture;
	sf::Vector2i gridPosition;
	sf::RenderStates state;
};

