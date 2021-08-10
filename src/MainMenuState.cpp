#include "pch.h"
#include "MainMenuState.h"

MainMenuState::MainMenuState(StateData& state_data, sf::String&& path) : State(state_data)
{
	//Init backgorund
	this->bgTexture.loadFromFile(path);
	state.texture = &this->bgTexture;
	this->background.resize(4, sf::Vertex());
	gui::setVectorShape(this->background);
	gui::setVectorShape(this->background, sf::FloatRect(0.f, 0.f, 800.f, 800.f), 0);
	//buttons
	this->buttons.push_back(gui::Button(sf::FloatRect(200.f,200.f,200.f,85.f), "PLAY", this->font, 70));
	this->buttons.push_back(gui::Button(sf::FloatRect(200.f, 350.f, 200.f, 85.f), "QUIT", this->font, 70));	
	//keytime
	this->btnsTime = std::make_unique<Keytime>(0.f, 20.f);

}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::update(const float& dt)
{
	this->btnsTime->update(dt);
	this->updateMousePosition();
	for (auto& i : this->buttons)
	{
		i.update(this->mousePosWindow);
	}
	if (this->buttons[0].clicked)
	{
		if(this->btnsTime->get())
			this->stateData.states.push(std::make_unique<GameState>(this->stateData));
		this->buttons[0].clicked = 0;
	}	
	else if (this->buttons[1].clicked)
	{
		if (this->btnsTime->get())
			this->stateData.states.pop();
	}
		


}

void MainMenuState::render()
{
	this->stateData.window.draw(&background[0], 4, sf::Quads, state);
	
	for (auto& i : this->buttons)
	{
		i.render(this->stateData.window);
	}
}
