#pragma once
#include "IWindowActivity.h"


class Menu : public IWindowActivity
{
public:
	
	Menu();
	Menu(sf::VideoMode videoMode_, sf::String windowTitle_);
private:
	 sf::RectangleShape btnStartGame;

	 void HandleInput() override;

	 void Update() override;

	 void Draw() override;

	 void Run() override;

	 void InnitGUI();

};

