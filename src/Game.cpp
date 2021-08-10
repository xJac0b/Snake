#include "pch.h"
#include "Game.h"
Game::Game()
{
	//Init window
    this->window = std::make_unique<sf::RenderWindow>(sf::VideoMode(600, 600), "Snake", sf::Style::Titlebar | sf::Style::Close);
    //Init State Data
    this->stateData = std::make_unique<StateData>(*this->window, this->states, this->event, 36.f);
    //Push state  
    this->states.push(std::make_unique<MainMenuState>(*this->stateData,"Resources/Images/MainMenuBackground.jpg"));

}

Game::~Game()
{
}

void Game::updateDt()
{
    this->dt = this->dtClock.restart().asSeconds(); //Delta time
    //std::cout << "FPS: " << 1.0f / dt << "\n";
    //system("cls");
}

void Game::updateSfmlEvents()
{
    while (window->pollEvent(this->event))
    {
        if(!this->states.empty())
            this->states.top()->updateSfmlEvents();
        if (event.type == sf::Event::Closed)
            window->close();
        
    }
}

void Game::update()
{
    this->updateDt();
    this->updateSfmlEvents();
    
    if (!this->states.empty())
    {
        if (this->window->hasFocus())
        {
            this->states.top()->update(this->dt); // update things in state
        }
    }
    else
        this->window->close();
}

void Game::render()
{
        window->clear();

        if (!this->states.empty())
            this->states.top()->render(); // render things in state

        window->display();
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->update();
        this->render();
    }
}
