#pragma once
#include "IWindowActivity.h"
#include <SFML/Graphics.hpp>

class Menu : public IWindowActivity
{
public:
    Menu();
    Menu(sf::VideoMode videoMode_, sf::String windowTitle_);

private:
    sf::RectangleShape btnStartGame; // ������ "������ � ������"
    sf::Text btnText;                // ����� �� ������
    sf::Font font;                   // ����� ��� ������

    void HandleInput() override;     // ��������� �����
    void Update() override;          // ���������� ���������
    void Draw() override;            // ��������� ����
    void Run() override;             // ������ ���������� ����

    void InitGUI();                  // ������������� ������������ ���������� (���������� �������� ������)
};
