#include "pch.h"
#include "Snake.h"

Snake::Snake(sf::FloatRect&& bounds, sf::Texture& texture, float& grid_size) : Entity(bounds, texture, grid_size), dir(1.f, 0.f), key(' '), logDirBack(0.f,0.f)
{ 
	gui::setVectorShape(this->sprite, sf::FloatRect(256.f, 0.f, 64.f, 62.f), 0);
	this->keyTime = std::make_unique<Keytime>(0.f, 10.f);
	this->snakeTime = std::make_unique<Keytime>(0.f, 15.f);
	
	this->grow(); this->grow();
}

Snake::~Snake()
{
}
	
const bool Snake::touchTail() const
{
	for (auto& i : this->tail)
	{
		if (this->gridPosition == i.getGridPos())
			return true;
	}
	return false;
}

const std::vector<SnakePart>& Snake::getTail() const
{
	return this->tail;
}

void Snake::move()
{
	this->tail.begin()->getDir() = this->dir; //set dir to first element of tail (next to head)
	if (this->key != ' ')
	{
		switch (this->key)
		{
		case 'W':
			this->dir = { 0.f,-1.f };
			gui::setVectorShape(this->sprite, sf::FloatRect(192.f, 0.f, 64.f, 64.f), 0);
			break;
		case 'S':
			this->dir = { 0.f,1.f };
			gui::setVectorShape(this->sprite, sf::FloatRect(256.f, 64.f, 64.f, 64.f), 0);
			break;
		case 'A':
			this->dir = { -1.f, 0.f };
			gui::setVectorShape(this->sprite, sf::FloatRect(192.f, 64.f, 64.f, 64.f), 0);
			break;
		case 'D':
			this->dir = { 1.f, 0.f };
			gui::setVectorShape(this->sprite, sf::FloatRect(256.f, 0.f, 64.f, 64.f), 0);
			break;
		}
		key = ' ';
	} // set dir to head
	std::vector<SnakePart>::iterator i = this->tail.end();
	while (i != this->tail.begin()) //from end of tail to begin
	{
		--i;
			sf::Vector2f b; // i->getDir() -> b
			if (i == this->tail.begin())
				b = this->dir;
			else
				b = (i - 1)->getDir();
			
			if (i->getDir().x != b.x)
			{
				if (i->getDir().x > b.x && b.y == 1.f ||
					i->getDir().y < b.y && b.x == -1.f)
					i->setTurn(1);
				
				else if (i->getDir().x < b.x && b.y == 1.f ||
					i->getDir().y < b.y && b.x == 1.f)
					i->setTurn(2);

				else if (i->getDir().x < b.x && b.y == -1.f ||
					i->getDir().y > b.y && b.x == 1.f)
					i->setTurn(3);
				
				else if (i->getDir().x > b.x && b.y == -1.f ||
					i->getDir().y > b.y && b.x == -1.f)
					i->setTurn(4);
			}
			else i->setTurn();
			
			i->getDir() = b;
			if(i == this->tail.begin())
				gui::setVectorShape(i->getVArray(), this->getBounds());
			else
				gui::setVectorShape(i->getVArray(), (i-1)->getBounds());
			
	}	
	for (auto& i : this->sprite)
	{
		i.position.x += this->gridSize * this->dir.x;
		i.position.y += this->gridSize * this->dir.y;
	}
}


void Snake::grow()
{
	sf::Vector2f t;
	if (this->tail.size() > 0)
	{
		float a, b;
		switch (this->tail.back().getTurn())
		{
		case 1:
			if (this->tail.back().getDir().x)
			{
				a = 0.f;
				b = 1.f;
			}
			else
			{
				a = -1.f;
				b = 0.f;
			}	
			break;
		case 2:
			if (this->tail.back().getDir().x)
			{
				a = 0.f;
				b = 1.f;
			}
			else
			{
				a = 1.f;
				b = 0.f;
			}
			break;
		case 3:
			if (this->tail.back().getDir().x)
			{
				a = 0.f;
				b = -1.f;
			}
			else
			{
				a = 1.f;
				b = 0.f;
			}
			break;
		case 4:
			if (this->tail.back().getDir().x)
			{
				a = 0.f;
				b = -1.f;
			}
			else
			{
				a = -1.f;
				b = 0.f;
			}
			break;
		default:
			a = -this->tail.back().getDir().x;
			b = -this->tail.back().getDir().y;
		}
		t = sf::Vector2f(this->tail.back().getPosition().x + this->gridSize * a ,
			this->tail.back().getPosition().y + this->gridSize * b);
	}
	else
		t = sf::Vector2f(this->getPosition().x + this->gridSize * -this->dir.x,
			this->getPosition().y + this->gridSize * -this->dir.y);
	
	this->tail.push_back(SnakePart(sf::FloatRect(t, sf::Vector2f(this->gridSize, this->gridSize)), this->texture, this->tail.size() < 2 ? this->dir : this->logDirBack,
		this->gridSize));
}

void Snake::update(const float& dt)
{
	this->logDirBack = this->tail.back().getDir();
	this->snakeTime->update(dt);
	this->keyTime->update(dt);

	if (this->dir.y == 0.f)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			if (this->keyTime->get())
				key = 'W';
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			if (this->keyTime->get())
				key = 'S';
		}

	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			if (this->keyTime->get())
				key = 'A';
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			if (this->keyTime->get())
				key = 'D';
		}
	}

	if (this->snakeTime->get())
		this->move();

	for (auto it = this->tail.begin(); it != this->tail.end(); it++)
	{
		it->update(dt);
		sf::FloatRect tt;
		if (it == --this->tail.end())
		{
			sf::Vector2f t = (it-1)->getDir();
			if (t.x > 0 && it->getDir().x > 0 || t.y < 0 && it->getDir().x > 0 || t.y > 0 && it->getDir().x > 0)
				tt = sf::FloatRect(256.f, 128.f, 64.f, 64.f);
			else if(t.x < 0 && it->getDir().x < 0 || t.y > 0 && it->getDir().x < 0 || t.y < 0 && it->getDir().x < 0)
				tt = sf::FloatRect(192.f, 192.f, 64.f, 64.f);
			else if (t.y > 0 && it->getDir().y > 0 || t.x > 0 && it->getDir().y > 0 || t.x < 0 && it->getDir().y > 0)
				tt = sf::FloatRect(256.f, 192.f, 64.f, 64.f);
			else if (t.y < 0 && it->getDir().y < 0 || t.x > 0 && it->getDir().y < 0 || t.x < 0 && it->getDir().y < 0)
				tt = sf::FloatRect(192.f, 128.f, 64.f, 64.f);
		}
		else
		{
			switch (it->getTurn())
			{
			case 1:
				tt = { 128.f, 0.f, 64.f,64.f };
				break;
			case 2:
				tt = { 0.f, 0.f, 64.f,64.f };
				break;
			case 3:
				tt = { 0.f, 64.f, 64.f,64.f };
				break;
			case 4:
				tt = { 128.f, 128.f, 64.f,64.f };
				break;
			default:
				if(it->getDir().x)
					tt = { 64.f, 0.f, 64.f,64.f };
				else
					tt = { 128.f, 64.f, 64.f,64.f };
				break;
			}
		}
		gui::setVectorShape(it->getVArray(), tt, 0);
	}
	this->updateGridPos();
}

void Snake::render(sf::RenderTarget& target)
{
	for (auto& i : this->tail)
		i.render(target);
	target.draw(&this->sprite[0], 4, sf::Quads, this->state);
}





// SNAKE PART // SNAKE PART // SNAKE PART // SNAKE PART // SNAKE PART // SNAKE PART // SNAKE PART // SNAKE PART
SnakePart::SnakePart(sf::FloatRect&& bounds, sf::Texture& texture, sf::Vector2f dir, float& gridSize) : Entity(bounds, texture, gridSize), dir(dir), turn(0)
{
	
}

SnakePart::~SnakePart()
{
}

void SnakePart::setTurn(short x)
{
	this->turn = x;
}

short& SnakePart::getTurn()
{
	return this->turn;
}

sf::Vector2f& SnakePart::getDir()
{
	return this->dir;
}

std::vector<sf::Vertex>& SnakePart::getVArray()
{
	return this->sprite;
}

void SnakePart::update(const float& dt)
{
	this->updateGridPos();
}

void SnakePart::render(sf::RenderTarget& target)
{
	target.draw(&this->sprite[0], 4, sf::Quads, this->state);
}
