#include "pch.h"
#include "Gui.h"

namespace gui
{
	void setVectorShape(std::vector<sf::Vertex>& varray, sf::FloatRect bounds, bool pos)
	{
		if (pos)
		{
			varray[0].position = sf::Vector2f(bounds.left, bounds.top);
			varray[1].position = sf::Vector2f(bounds.left + bounds.width, bounds.top);
			varray[2].position = sf::Vector2f(bounds.left + bounds.width, bounds.top + bounds.height);
			varray[3].position = sf::Vector2f(bounds.left, bounds.top + bounds.height);
		}
		else
		{
			varray[0].texCoords = sf::Vector2f(bounds.left, bounds.top);
			varray[1].texCoords = sf::Vector2f(bounds.left + bounds.width, bounds.top);
			varray[2].texCoords = sf::Vector2f(bounds.left + bounds.width, bounds.top + bounds.height);
			varray[3].texCoords = sf::Vector2f(bounds.left, bounds.top + bounds.height);
		}
	}
	sf::FloatRect getVectorShape(std::vector<sf::Vertex>& varray)
	{
		return sf::FloatRect(varray[0].position.x, varray[0].position.y, varray[1].position.x - varray[0].position.x,
			varray[2].position.y - varray[1].position.y);
	}

	
	Button::Button(sf::FloatRect&& bounds, sf::String&& text, sf::Font& font, unsigned&& charSize, sf::Color text_idle, sf::Color text_hover, sf::Color text_active,
		sf::Color idle, sf::Color hover, sf::Color active,
		sf::Color out_idle, sf::Color out_hover, sf::Color out_active) : bounds(bounds), textIdle(text_idle), textHover(text_hover), textActive(text_active),
		idle(idle), hover(hover), active(active), outIdle(out_idle), outHover(out_hover), outActive(out_active), state(BTN_STATES::IDLE), clicked(false)
	{
		this->shape.resize(4, sf::Vertex());
		this->outline.resize(5, sf::Vertex());

		//Shape
		setVectorShape(this->shape, this->bounds);

		for (auto i : this->shape)
			i.color = this->idle;

		//Outline
		setVectorShape(this->outline, sf::FloatRect(this->bounds.left - 1.f, this->bounds.top - 1.f, this->bounds.width + 2.f, this->bounds.height + 2.f));
		this->outline[4].position = this->outline[0].position;

		for (auto i : this->outline)
			i.color = this->outIdle;

		//Text 
		this->text.setString(text);
		this->text.setFont(font);
		this->text.setCharacterSize(charSize);
		this->text.setPosition(sf::Vector2f(bounds.left + (bounds.width / 2.f) - this->text.getGlobalBounds().width / 2.f,
			bounds.top + (bounds.height / 3.7f) - this->text.getGlobalBounds().height / 2.f));
		this->text.setFillColor(this->textIdle);

		//init sound
		this->buffer.loadFromFile("Resources/Sounds/click.wav");
	}

	Button::~Button()
	{
	}

	void Button::setColor(sf::Color& color, sf::Color& out_color)
	{
		for (auto& i : this->shape)
			i.color = color;
		for (auto& i : this->outline)
			i.color = out_color;
	}

	void Button::update(sf::Vector2i& mousePosWin)
	{
		if (bounds.contains(static_cast<sf::Vector2f>(mousePosWin)))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				this->state = BTN_STATES::ACTIVE;
				this->text.setFillColor(this->textActive);
				this->setColor(this->active, this->outActive);
			}
			else
			{
				if (this->state == BTN_STATES::ACTIVE)
				{
					this->sound.setBuffer(this->buffer);
					this->sound.play();
					do 
					{
					} while (!this->sound.getStatus() == sf::Sound::Stopped);
					this->clicked = true;
				}
					
				this->state = BTN_STATES::HOVER;
				this->text.setFillColor(this->textHover);
				this->setColor(this->hover, this->outHover);
			}
		}
		else
		{
			this->state = BTN_STATES::IDLE;
			this->text.setFillColor(this->textIdle);
			this->setColor(this->idle, this->outIdle);
		}

	}

	void Button::render(sf::RenderTarget& target)
	{
		target.draw(&this->shape[0], 4, sf::Quads);
		target.draw(&this->outline[0], 5, sf::LinesStrip);
		target.draw(this->text);
	}

}