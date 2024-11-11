#include "Menu.h"
#include "WindowStateManager.h"
#include<iostream>

Menu::Menu() {
    InitGUI();
}

Menu::Menu(sf::VideoMode videoMode_, sf::String windowTitle_)
    : IWindowActivity(videoMode_, windowTitle_) {
    InitGUI();
}
void Menu::HandleInput() {
    sf::Event event;
    while (window->pollEvent(event)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

        if (btnStartGame.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            btnStartGame.setFillColor(sf::Color(90, 160, 210));  
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                btnStartGame.setFillColor(sf::Color(50, 100, 150));  
                WindowStateManager::getInstance().createGame();
            }
        }
        else {
            btnStartGame.setFillColor(sf::Color(70, 130, 180));  
        }

        if (event.type == sf::Event::Closed)
            window->close();
    }
}


void Menu::Update() {

}

void Menu::Draw() {
    window->clear(sf::Color::Cyan); 

    window->draw(btnStartGame);
    window->draw(btnText);

    window->display();
}

void Menu::Run() {
    IWindowActivity::Run();
}
void Menu::InitGUI() {

    btnStartGame.setSize(sf::Vector2f(220, 80));
    btnStartGame.setFillColor(sf::Color(30, 60, 90));  
    btnStartGame.setOutlineColor(sf::Color(10, 30, 60));  
    btnStartGame.setOutlineThickness(5);
    btnStartGame.setPosition(window->getSize().x / 2 - 110, window->getSize().y / 2  - 55);


    if (!font.loadFromFile(".../../Fonts/beer money.ttf")) {
        std::cerr << "Failed to load font!\n";
    }

    btnText.setFont(font);
    btnText.setString("Play with Friend");
    btnText.setFillColor(sf::Color::White);  

    
    btnText.setPosition(
        btnStartGame.getPosition().x + (btnStartGame.getSize().x - btnText.getGlobalBounds().width) / 2,
        btnStartGame.getPosition().y + (btnStartGame.getSize().y - btnText.getGlobalBounds().height) / 2 - 5
    );
}

