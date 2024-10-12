#pragma once
#include "IWindowActivity.h"
class Game : public IWindowActivity
{
	public:

		Game();
		Game(sf::VideoMode videoMode_, sf::String windowTitle_);
	private:
		const uint16_t offsetXForGamePrompt = 254;
		const uint16_t offsetYForGamePrompt = 18;
		const uint16_t TileSize = 75;

		const char columnsLabels[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };

		sf::Vector2f selectedTileIndex{-1, -1};

		void HandleInput() override;

		void Update() override;

		void Draw() override;

		void Run() override;

		void InnitGUI();

	};




