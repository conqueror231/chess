#include "Menu.h"
#include "WindowStateManager.h"
#include<iostream>

const sf::Vector2f Menu::BTN_START_GAME_POSITION(315, 543);
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
            btnStartGame.setFillColor(sf::Color(255, 255, 255, 100));
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                btnStartGame.setFillColor(sf::Color(255, 255, 255, 255));
                WindowStateManager::getInstance().createGame();
            }
        }
        else {
            btnStartGame.setFillColor(sf::Color(255, 255, 255, 50));
        }

        if (event.type == sf::Event::Closed)
            window->close();
    }
}


void Menu::Draw() {
    window->clear(sf::Color::Cyan); 

    sf::Sprite background;
    sf::Texture text;
    text.loadFromFile("Img/MenuBackground.png");
    background.setTexture(text);
    background.setPosition(0, 0);

    window->draw(background);
    window->draw(btnStartGame);
    window->display();
}

void Menu::Run() {
    IWindowActivity::Run();
}
void Menu::InitGUI() {
    sf::Uint8 transparentPixel[4] = { 255, 255, 255, 0 };
    window->setIcon(1, 1, transparentPixel);

    btnStartGame.setSize(sf::Vector2f(380, 90));
    btnStartGame.setPosition(BTN_START_GAME_POSITION);

}

