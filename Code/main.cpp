#include <SFML/Graphics.hpp>
#include "Classes/WindowStateManager.h"
#include "Classes/Menu.h"

WindowStateManager* WStateManager;

int main()
{
    WStateManager = &WindowStateManager::getInstance();

    std::unique_ptr<IWindowActivity> wMenu = std::make_unique<Menu>(sf::VideoMode(500, 500), "My Menu");
 
    WStateManager->setState(std::move(wMenu));
    WStateManager->RunState();


    return 0;
}