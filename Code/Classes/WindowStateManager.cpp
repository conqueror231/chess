#include "WindowStateManager.h"
#include "Menu.h"
#include "Game.h"
#include <iostream>
void WindowStateManager::InnitWindow(sf::VideoMode WindowSize, sf::String title)
{
	if (window)
		return;
	window = std::make_unique<sf::RenderWindow>(WindowSize, title, sf::Style::Close);
}
sf::RenderWindow& WindowStateManager::GetWindow()
{
	if (window == nullptr) {
		InnitWindow({ 1024,768 }, "untitled");
	}
	return *window;
}
void WindowStateManager::createMenu() {
	std::unique_ptr<IWindowActivity> wMenu = std::make_unique<Menu>();
	setState(std::move(wMenu));
	RunState();
}

void WindowStateManager::createGame()
{
	std::cout << "Current state address: " << currentState.get() << std::endl;
	std::unique_ptr<IWindowActivity> wGame = std::make_unique<Game>(sf::VideoMode{ 1024,768 }, "Chess Game");
	setState(std::move(wGame));
	RunState();
}

void WindowStateManager::setState(std::unique_ptr<IWindowActivity> newState)
{

	currentState.reset();


	currentState = std::move(newState);
}

void WindowStateManager::RunState()
{
	currentState->Run();
}
