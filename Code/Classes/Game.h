#pragma once
#include "IWindowActivity.h"
class Game : public IWindowActivity
{
	public:

		Game();
		Game(sf::VideoMode videoMode_, sf::String windowTitle_);
	private:
		const uint16_t offsetXForChessBoard = 254;
		const uint16_t offsetYForChessBoard = 18;
		const uint16_t TileSize = 75;

		const char columnsLabels[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };

		sf::Vector2f hoveredTileIndexes{-1, -1};
		class Tile* selectedTile;

		class ChessBoard* chessBoard;

		void HandleInput() override;

		void Update() override;

		void Draw() override;

		void Run() override;

		void InnitGUI();

	};




