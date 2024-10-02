#include <SFML/Graphics.hpp>
#include "Classes/WindowStateManager.h"
#include "Classes/Menu.h"

WindowStateManager* WStateManager;

int main()
{
  
    WStateManager = &WindowStateManager::getInstance();
    WStateManager->InnitWindow({ 500,500 }, "Main Menu");

    std::unique_ptr<IWindowActivity> wMenu = std::make_unique<Menu>();
 
    WStateManager->setState(std::move(wMenu));
    WStateManager->RunState();
  
 
  

    return 0;
}