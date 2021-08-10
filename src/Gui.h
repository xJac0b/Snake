#pragma once
enum class BTN_STATES { IDLE, HOVER, ACTIVE };
namespace gui
{
	void setVectorShape(std::vector<sf::Vertex>& varray, sf::FloatRect bounds = sf::FloatRect(0.f, 0.f, 600.f, 600.f), bool pos = 1);
	sf::FloatRect getVectorShape(std::vector<sf::Vertex>& varray);
	class Button
	{
	public:
		//Ctor,dtor
		Button(sf::FloatRect&& bounds, sf::String&& text, sf::Font& font, unsigned&& charSize,
			sf::Color text_idle = sf::Color::Yellow, sf::Color text_hover = sf::Color::White, sf::Color text_active = sf::Color::Black,
			sf::Color idle = sf::Color::Transparent, sf::Color hover = sf::Color::Transparent, sf::Color active = sf::Color::Transparent,
			sf::Color out_idle = sf::Color::Transparent, sf::Color out_hover = sf::Color::Transparent, sf::Color out_active = sf::Color::Transparent);
		~Button();
		//Functions
		void setColor(sf::Color& color, sf::Color& out_color);
		void update(sf::Vector2i& mousePosWin);
		void render(sf::RenderTarget& target);

		bool clicked;

	private:
		sf::SoundBuffer buffer;
		sf::Sound sound;
		std::vector<sf::Vertex>shape;
		std::vector<sf::Vertex>outline;
		sf::Text text;
		sf::FloatRect bounds;
		BTN_STATES state;


		sf::Color textIdle;
		sf::Color textHover;
		sf::Color textActive;
		sf::Color idle;
		sf::Color hover;
		sf::Color active;
		sf::Color outIdle;
		sf::Color outHover;
		sf::Color outActive;
	};
}