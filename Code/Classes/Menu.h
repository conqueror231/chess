#pragma once
#include "IWindowActivity.h"
#include <SFML/Graphics.hpp>

class Menu : public IWindowActivity
{
public:
    Menu();
    Menu(sf::VideoMode videoMode_, sf::String windowTitle_);

private:
    static const sf::Vector2f BTN_START_GAME_POSITION;
    sf::RectangleShape btnStartGame; 
    sf::Font font;                

    void HandleInput() override;        
    void Draw() override;          
    void Run() override;           

    void InitGUI();                  
};
