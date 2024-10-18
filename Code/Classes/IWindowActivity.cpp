#include "IWindowActivity.h"
#include "WindowStateManager.h"
#include "iostream"
void IWindowActivity::Run()
{
	while (window->isOpen()) {
		HandleInput();
		Update();
		Draw();
	}
}

IWindowActivity::IWindowActivity(sf::VideoMode videoMode_, sf::String windowTitle_)
{
	window = &WindowStateManager::getInstance().GetWindow();

	window->setTitle(windowTitle_);
	window->setSize(sf::Vector2u(videoMode_.width, videoMode_.height));

}

IWindowActivity::IWindowActivity()
{
	window = &WindowStateManager::getInstance().GetWindow();
}



