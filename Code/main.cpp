#include <SFML/Graphics.hpp>
#include "Classes/WindowStateManager.h"
#include "Classes/Menu.h"

WindowStateManager* WStateManager;

int main()
{
  
    WStateManager = &WindowStateManager::getInstance();
    WStateManager->InnitWindow({ 500,500 }, "Main Menu");

    WStateManager->createMenu();
 
  

    return 0;
}