#include <SFML/Graphics.hpp>
#include "Classes/WindowStateManager.h"
#include "Classes/Menu.h"

WindowStateManager* WStateManager;

int main()
{
  
    WStateManager = &WindowStateManager::getInstance();
    WStateManager->InnitWindow({ 1024,768 }, "Main Menu");

    WStateManager->createMenu();
    
  

    return 0;
}