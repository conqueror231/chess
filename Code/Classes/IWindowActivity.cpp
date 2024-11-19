#include "IWindowActivity.h"
#include "WindowStateManager.h"
#include "iostream"
void IWindowActivity::Run()
{
	while (window->isOpen()) {
		HandleInput();
		Draw();
	}
}

IWindowActivity::IWindowActivity(sf::VideoMode videoMode_, sf::String windowTitle_)
{
	window = &WindowStateManager::getInstance().GetWindow();

	window->setTitle(windowTitle_);
	window->setSize(sf::Vector2u(videoMode_.width, videoMode_.height));
	sf::Uint8 transparentPixel[4] = { 255, 255, 255, 0 };
	window->setIcon(1, 1, transparentPixel);
}

IWindowActivity::IWindowActivity()
{
	window = &WindowStateManager::getInstance().GetWindow();
}



