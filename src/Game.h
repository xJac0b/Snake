#pragma once
#include "MainMenuState.h"
class Game
{
public:
	//ctor, dtor
	Game();
	~Game();
	//functions
	void updateDt();
	void updateSfmlEvents();
	void update();
	void render();
	void run();
private:
	std::unique_ptr<sf::RenderWindow> window;
	sf::Event event;
	sf::Clock dtClock;
	std::stack<std::unique_ptr<State>>states;
	std::unique_ptr<StateData> stateData;
	float dt;
};

