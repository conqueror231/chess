#include "Menu.h"

Menu::Menu()
{
  
    InnitGUI();
}

Menu::Menu(sf::VideoMode videoMode_, sf::String windowTitle_)
    : IWindowActivity(videoMode_, windowTitle_) 
{
    InnitGUI();

}

void Menu::HandleInput()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

            if (btnStartGame.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y)) {
                
                btnStartGame.setFillColor(sf::Color::Green);
            }

        }

        if (event.type == sf::Event::Closed)
            window->close();
    }
}

void Menu::Update()
{
   
}

void Menu::Draw()
{


    
   



    window->clear();
    window->draw(btnStartGame);

    window->display();
    
}

void Menu::Run()
{
    IWindowActivity::Run();
}

void Menu::InnitGUI()
{
    btnStartGame.setSize(sf::Vector2f(100,50));
    btnStartGame.setOutlineColor(sf::Color::Red);
    btnStartGame.setOutlineThickness(5);
    btnStartGame.setPosition(window->getSize().x / 2 - 50, window->getSize().y / 2);
}
