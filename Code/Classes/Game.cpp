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
    window->clear();


    window->display();
}

void Game::Run()
{
    IWindowActivity::Run();
}

void Game::InnitGUI()
{

}
