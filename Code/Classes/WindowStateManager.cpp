#include "WindowStateManager.h"
#include "Menu.h"
#include "Game.h"
void WindowStateManager::createMenu() {
	std::unique_ptr<IWindowActivity> wMenu = std::make_unique<Menu>();
	setState(std::move(wMenu));
	RunState();
}

void WindowStateManager::createGame()
{
	std::unique_ptr<IWindowActivity> wGame = std::make_unique<Game>();
	setState(std::move(wGame));
	RunState();
}
