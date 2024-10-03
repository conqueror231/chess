#include "Menu.h"

Menu::Menu()
{
  

}

Menu::Menu(sf::VideoMode videoMode_, sf::String windowTitle_)
    : IWindowActivity(videoMode_, windowTitle_) 
{

}

void Menu::HandleInput()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
    }
}

void Menu::Update()
{
   
}

void Menu::Draw()
{

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);


        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }


        window->clear();
        window->draw(shape);
        window->display();
    
}

void Menu::Run()
{
    IWindowActivity::Run();
}
