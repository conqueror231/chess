#pragma once
#include "IWindowActivity.h"
#include <SFML/Graphics.hpp>

class Menu : public IWindowActivity
{
public:
    Menu();
    Menu(sf::VideoMode videoMode_, sf::String windowTitle_);

private:
    sf::RectangleShape btnStartGame; // Кнопка "Играть с другом"
    sf::Text btnText;                // Текст на кнопке
    sf::Font font;                   // Шрифт для текста

    void HandleInput() override;     // Обработка ввода
    void Update() override;          // Обновление состояния
    void Draw() override;            // Отрисовка окна
    void Run() override;             // Запуск активности окна

    void InitGUI();                  // Инициализация графического интерфейса (исправлено название метода)
};
