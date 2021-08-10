#pragma once
#include "GameState.h"
class MainMenuState :
    public State
{
public:
    MainMenuState(StateData& state_data, sf::String&& path);
    ~MainMenuState();
    void update(const float& dt);
    void render();
private:
    std::vector<sf::Vertex>background;
    sf::Texture bgTexture;
    sf::RenderStates state;
    std::vector<gui::Button>buttons;
    std::unique_ptr<Keytime> btnsTime;
};

