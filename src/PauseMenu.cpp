#include "pch.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::Font& font) : font(font), paused(false)
{
	//Init background
	this->background.resize(4, sf::Vertex());
	gui::setVectorShape(this->background);
	for (auto& i : this->background)
		i.color = sf::Color(50, 50, 50, 150);
	//Init panel
	this->panel.resize(4, sf::Vertex());
	gui::setVectorShape(this->panel, { 150.f,0.f,300.f,600.f });
	for (auto& i : this->panel)
		i.color = sf::Color(10, 10, 10, 200);
	//Init Buttons
	this->buttons.push_back(gui::Button(sf::FloatRect(150.f, 100.f, 300.f, 85.f), "Resume", this->font, 60));
	this->buttons.push_back(gui::Button(sf::FloatRect(150.f, 380.f, 300.f, 85.f), "Restart", this->font, 60));
	this->buttons.push_back(gui::Button(sf::FloatRect(150.f, 500.f, 300.f, 85.f), "Quit", this->font, 60));
}

PauseMenu::~PauseMenu()
{
}

const bool& PauseMenu::isPaused() const
{
	return this->paused;
}

void PauseMenu::pause()
{
	this->paused = !this->paused;
}

const bool PauseMenu::isBtnClicked(short n)
{
	if (this->buttons[n].clicked)
	{
		this->buttons[n].clicked = false;
		return true;
	}
	return false;
		
}

void PauseMenu::update(const float& dt, sf::Vector2i& mouse_pos_win)
{
	for (auto& i : this->buttons)
		i.update(mouse_pos_win);
}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(&this->background[0], 4, sf::Quads);
	target.draw(&this->panel[0], 4, sf::Quads);
	for (auto& i : this->buttons)
		i.render(target);
}
