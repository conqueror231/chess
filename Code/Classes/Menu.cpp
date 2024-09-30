#include "Menu.h"



Menu::Menu(sf::VideoMode videoMode_, sf::String windowTitle_)
    : IWindowActivity(videoMode_, windowTitle_) 
{

}

void Menu::HandleInput()
{
  
}

void Menu::Update()
{
   
}

void Menu::Draw()
{

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

}

void Menu::Run()
{
    IWindowActivity::Run();
}
