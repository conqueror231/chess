#include "Game.h"
#include "WindowStateManager.h"
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
     

        if (event.type == sf::Event::Closed)
            window->close();
    }
}

void Game::Update()
{

}

void Game::Draw()
{
    window->clear(sf::Color::Cyan);
    
    const int tileSize = 100;


    sf::Color lightColor = sf::Color::White;
    sf::Color darkColor = sf::Color::Black;

    int offsetx = 190;
    int offsety = 50;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
           
            sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));

         
            tile.setPosition(col * tileSize + offsetx, row * tileSize + offsety);

            if ((row + col) % 2 == 0) {
                tile.setFillColor(lightColor); 
            }
            else {
                tile.setFillColor(darkColor);  
            }

           
            window->draw(tile);
        }
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
