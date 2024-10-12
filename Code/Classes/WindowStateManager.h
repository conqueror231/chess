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
	void InnitWindow(sf::VideoMode WindowSize, sf::String title ) {
		if (window)
			return;
			
		window = std::make_unique<sf::RenderWindow>(WindowSize, title);
		
	}


	sf::RenderWindow& GetWindow() {
		if (window == nullptr) {
			InnitWindow({ 1024,768 }, "untitled");
		}
		return * window;
	}

	WindowStateManager(const WindowStateManager&) = delete;

	WindowStateManager& operator=(const WindowStateManager&) = delete;

	static WindowStateManager& getInstance() {
		static WindowStateManager instance;
		return instance;
}

	void createMenu();
	void createGame();

	void setState(std::unique_ptr<IWindowActivity> newState) {
		currentState = std::move(newState);
	}

	void RunState() {
		currentState->Run();
	}


};

