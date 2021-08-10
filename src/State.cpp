#include "pch.h"
#include "State.h"

State::State(StateData& state_data) : stateData(state_data)
{
	this->font.loadFromFile("Fonts/font1.ttf");
}

State::~State()
{
}

void State::updateSfmlEvents()
{
}

void State::updateMousePosition()
{
	this->mousePosWindow = sf::Mouse::getPosition(this->stateData.window);
}