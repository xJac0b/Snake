#include "pch.h"
#include "GameState.h"

GameState::GameState(StateData& state_data) : State(state_data), end(0)
{
	this->textures["SNAKE&APPLE"].loadFromFile("Resources/Images/snake.png");
	this->textures["WALLS"].loadFromFile("Resources/Images/walls.jpg");
	this->textures["WIN"].loadFromFile("Resources/Images/win.png"); 
	this->textures["DEFEAT"].loadFromFile("Resources/Images/lose.png");
	this->state.texture = &this->textures["WALLS"];
	this->background.resize(4, sf::Vertex());
	gui::setVectorShape(this->background);
	gui::setVectorShape(this->background, { 0.f,0.f,800.f,800.f }, 0);
	
	this->board = std::make_unique<Board>(this->stateData.gridSize, 15, 15, this->textures["SNAKE&APPLE"], this->font);

	//init pause menu
	this->pauseMenu = std::make_unique<PauseMenu>(this->font);
	//Init text
	this->text.setFont(this->font);
	this->text.setCharacterSize(50);
	this->text.setPosition(200.f, 200.f);
	//Init endbox
	this->endBox.resize(4, sf::Vertex());
	gui::setVectorShape(this->endBox, { 0.f,200.f,600.f,150.f });
	gui::setVectorShape(this->endBox, { 0.f,0.f,600.f,150.f}, 0);

}

GameState::~GameState()
{
}

void GameState::gameOver()
{
	this->endState.texture = &this->textures["DEFEAT"];
	std::stringstream ss;
	ss << "YOU LOSE!\n   score: " << this->board->getScore();
	this->text.setString(ss.str());
}

void GameState::win()
{
	this->endState.texture = &this->textures["WIN"];
	std::stringstream ss;
	ss << "YOU WON!\n  score: " << this->board->getScore();
	this->text.setString(ss.str());
}

void GameState::updateSfmlEvents()
{
	if (this->stateData.sfEvent.type == sf::Event::KeyPressed)
		if (this->stateData.sfEvent.key.code == sf::Keyboard::Escape)
		{
			this->pauseMenu->pause();
		}
}

void GameState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateSfmlEvents();

	if (this->pauseMenu->isPaused())
	{
		this->pauseMenu->update(dt, this->mousePosWindow);
		if (this->pauseMenu->isBtnClicked(0))
		{
			this->pauseMenu->pause();
		}
		else if (this->pauseMenu->isBtnClicked(1))
		{
			this->end = false;
			this->board = std::make_unique<Board>(this->stateData.gridSize, 15, 15, this->textures["SNAKE&APPLE"], this->font);
			this->pauseMenu->pause();
		}
		else if (this->pauseMenu->isBtnClicked(2))
		{
			this->stateData.states.pop();
		}

	}	
	else if(!this->end)
	{
		this->board->update(dt);
		if (this->board->isTheEnd())
		{
			this->end = true;
			if(this->board->isTheEnd() == 1)
				this->gameOver();
			else if (this->board->isTheEnd() == 2)
				this->win();
		}	
	}
	
}

void GameState::render()
{
	this->stateData.window.draw(&this->background[0], 4, sf::Quads, this->state);
	this->board->render(this->stateData.window);
	if (this->end)
	{
		this->stateData.window.draw(&this->endBox[0], 4, sf::Quads, this->endState);
		this->stateData.window.draw(this->text);
	}
	if (this->pauseMenu->isPaused())
		this->pauseMenu->render(this->stateData.window);

}



// BOARD// BOARD// BOARD// BOARD// BOARD// BOARD// BOARD// BOARD
// BOARD// BOARD// BOARD// BOARD// BOARD// BOARD// BOARD// BOARD
Board::Board(float& grid_size, int width, int height, sf::Texture& texture, sf::Font& font) : gridSize(grid_size), width(width),
height(height), texture(texture), lose(0), win(0), countdownInt(4)
{
	this->timer.restart();
	this->countdown.setFont(font);
	this->countdown.setCharacterSize(220.f);
	this->countdown.setPosition({ 260.f,110.f });

	this->board.resize(15);
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			std::vector<sf::Vertex>temp(5, sf::Vertex());
			gui::setVectorShape(temp, sf::FloatRect(this->gridSize * (width - j), (this->gridSize * (height - i)),
				this->gridSize, this->gridSize));
			temp[4] = temp[0];
			for (auto& k : temp)
				k.color = sf::Color(200, 200, 200);
			this->board[i].insert(this->board[i].end(), temp.begin(), temp.end());
		}
	}
	this->background.resize(4, sf::Vertex());
	gui::setVectorShape(this->background, { 35.f,35.f,540.f,540.f});
	for (auto& i : this->background)
		i.color = sf::Color(30, 30, 30);

	this->snake = std::make_unique<Snake>(sf::FloatRect(290.f, 290.f, this->gridSize, this->gridSize), texture, this->gridSize);
	this->snake->update(0.f);
	this->apple = std::make_unique<Apple>(sf::FloatRect(0.f, 0.f, this->gridSize-5.f, this->gridSize-5.f), texture, this->gridSize);
	this->apple->newApple();
	this->bufferEat.loadFromFile("Resources/Sounds/eat.wav");
	this->bufferLose.loadFromFile("Resources/Sounds/lose.wav");
	this->bufferWin.loadFromFile("Resources/Sounds/win.wav");
	this->bufferCountDown.loadFromFile("Resources/Sounds/countdown.wav");
	this->sound.setBuffer(this->bufferCountDown);
}

Board::~Board()
{
}

const int& Board::getScore() const
{
	return this->snake->getTail().size() - 2;
}

const short Board::isTheEnd() const
{
	if (this->lose)
		return 1; 
	if (this->win)
		return 2;
	return 0;
}

void Board::update(const float& dt)
{
	if (this->countdownInt >= 0)
	{
		if(this->sound.getStatus() != sf::Sound::Playing && this->countdownInt== 3)
				this->sound.play();
		if (this->countdownInt - std::floor(this->timer.getElapsedTime().asSeconds()) < this->countdownInt)
		{
			
			this->countdownInt -= std::floor(this->timer.getElapsedTime().asSeconds());
			this->countdown.setString(std::to_string(this->countdownInt));
			this->timer.restart();
		}
		
	}
	else
	{
		if (this->apple->getGridPos() == this->snake->getGridPos())
		{
			if (this->snake->getTail().size() > 223)
			{
				this->sound.setBuffer(this->bufferWin);
				this->sound.play();
				this->win = true;
			}

			else
			{
				this->sound.setBuffer(this->bufferEat);
				this->sound.play();
				this->snake->grow();
				bool intersects;
				do {
					intersects = false;
					this->apple->newApple();
					if (this->apple->getGridPos() == this->snake->getGridPos())
						intersects = true;
					for (auto& i : this->snake->getTail())
					{
						if (i.getGridPos() == this->apple->getGridPos())
							intersects = true;
					}
				} while (intersects);
			}
		}
		this->snake->update(dt);
		if (this->snake->getGridPos().x >= this->width || this->snake->getGridPos().x < 0 ||
			this->snake->getGridPos().y >= this->height || this->snake->getGridPos().y < 0 || this->snake->touchTail())
		{
			this->sound.setBuffer(this->bufferLose);
			this->sound.play();
			this->lose = true;
		}
	}		
}

void Board::render(sf::RenderTarget& target)
{
	target.draw(&this->background[0], 4, sf::Quads);
	for(auto& i : this->board)
		target.draw(&i[0], 75, sf::LineStrip);
	this->snake->render(target);
	this->apple->render(target);
	if(this->countdownInt >= 0)
	
		target.draw(this->countdown);
	else
	{
	this->snake->render(target);
	}

	
}
