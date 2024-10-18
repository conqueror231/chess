#pragma once
#include <memory>
#include "IWindowActivity.h"
#include <SFML/Graphics.hpp>

class WindowStateManager
{
private:

std::unique_ptr<sf::RenderWindow> window;
std::unique_ptr<IWindowActivity> currentState;

WindowStateManager() {};

public:
	WindowStateManager(const WindowStateManager&) = delete;
	WindowStateManager& operator=(const WindowStateManager&) = delete;

	void InnitWindow(sf::VideoMode WindowSize, sf::String title);
	sf::RenderWindow& GetWindow();

	static WindowStateManager& getInstance() {
		static WindowStateManager instance;
		return instance;
}

	void createMenu();
	void createGame();
	void setState(std::unique_ptr<IWindowActivity> newState);
	void RunState();


};

