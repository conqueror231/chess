#include "Game.h"
#include "WindowStateManager.h"
#include <iostream>
Game::Game()
{

    InnitGUI();
}

Game::Game(sf::VideoMode videoMode_, sf::String windowTitle_)
    : IWindowActivity(videoMode_, windowTitle_)
{
    InnitGUI();

}

void Game::HandleInput()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        sf::Vector2i gamePromptStartPos(offsetXForGamePrompt, offsetYForGamePrompt);
        sf::Vector2i gamePromptEndPos(offsetXForGamePrompt + TileSize * 8,
                                                        offsetYForGamePrompt + TileSize * 8);
        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

        if (mousePos.x >= gamePromptStartPos.x && mousePos.x <= gamePromptEndPos.x &&
            mousePos.y >= gamePromptStartPos.y && mousePos.y <= gamePromptEndPos.y) {

            for (int x = 0; x < 8; x++) {
                if (mousePos.x >= gamePromptStartPos.x + TileSize * (x+1))
                    continue;
                 for (int y = 0; y < 8; y++) {
                      if (mousePos.y >= gamePromptStartPos.y + TileSize * (y + 1))
                         continue;

                      selectedTileIndex.x = x;
                      selectedTileIndex.y = y;
                      std::cout << "Row: " << y + 1 << ", Column: " << columnsLabels[x] << std::endl;
                      break;
                    }
                    break;
                }
            


        }
        else {
            selectedTileIndex.x = -1;
            selectedTileIndex.y = -1;
        }

            
          
        }

        if (event.type == sf::Event::Closed)
            window->close();
    }

void Game::Update()
{

}

void Game::Draw()
{
    window->clear(sf::Color::Cyan);
    
   // game prompt
    sf::Color lightColor = sf::Color::White;
    sf::Color darkColor(73, 84, 202);
   
    
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
           
            sf::RectangleShape tile(sf::Vector2f(TileSize, TileSize));

         
            tile.setPosition(col * TileSize + offsetXForGamePrompt, row * TileSize + offsetYForGamePrompt);

            if ((row + col) % 2 == 0) {
                tile.setFillColor(lightColor); 
            }
            else {
                tile.setFillColor(darkColor);  
            }

           
            window->draw(tile);
        }
    }

    //left side menu
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(203, 768));  // Устанавливаем размер
    rectangle.setFillColor(sf::Color(17, 140, 202));  // Устанавливаем цвет #118CCA
    window->draw(rectangle);

    if (selectedTileIndex.x != -1 && selectedTileIndex.y != -1) {
        sf::RectangleShape highlightedTile(sf::Vector2f(TileSize, TileSize));
        highlightedTile.setPosition(selectedTileIndex.x * TileSize + offsetXForGamePrompt,
        selectedTileIndex.y * TileSize + offsetYForGamePrompt);
        highlightedTile.setFillColor(sf::Color(255, 255, 0, 128));  // Полупрозрачный жёлтый цвет
        window->draw(highlightedTile);
    }

    window->display();
}

void Game::Run()
{
    IWindowActivity::Run();
}

void Game::InnitGUI()
{

}
