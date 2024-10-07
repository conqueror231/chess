#pragma once
#include "IWindowActivity.h"
class Game : public IWindowActivity
{
	public:

		Game();
		Game(sf::VideoMode videoMode_, sf::String windowTitle_);
	private:

		void HandleInput() override;

		void Update() override;

		void Draw() override;

		void Run() override;

		void InnitGUI();

	};




