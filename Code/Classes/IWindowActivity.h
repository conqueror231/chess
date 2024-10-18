#pragma once
#include <SFML/Graphics.hpp>

class IWindowActivity
{
public:
virtual void Run();

protected:
	sf::RenderWindow * window;
	sf::String windowTitle = "Default";
	sf::VideoMode videoMode { 500, 500 };

	virtual void HandleInput() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	
	IWindowActivity(sf::VideoMode videoMode_, sf::String windowTitle_);
	IWindowActivity();
};

