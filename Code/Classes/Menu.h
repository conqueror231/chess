#pragma once
#include "IWindowActivity.h"


class Menu : public IWindowActivity
{
public:
	
	Menu();
	Menu(sf::VideoMode videoMode_, sf::String windowTitle_);
private:

	 void HandleInput() override;

	 void Update() override;

	 void Draw() override;

	 void Run() override;


};

