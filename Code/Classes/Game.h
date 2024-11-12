#pragma once
#include "IWindowActivity.h"
#include "ChessPieces/PieceType.h"

class Game : public IWindowActivity
{
public:

	Game();
	Game(sf::VideoMode videoMode_, sf::String windowTitle_);
private:
	std::map<PieceType, std::pair<sf::Texture, sf::Texture>> pieceTextures;

	const uint16_t offsetXForChessBoard = 254;
	const uint16_t offsetYForChessBoard = 18;
	const uint16_t TileSize = 75;

	static const sf::Vector2f TURN_LABEL_POSITION;

	const char columnsLabels[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };

	sf::Vector2i hoveredTileIndexes{ -1, -1 };
	sf::Vector2i selectedTileIndexes{ -1, -1 };


	class ChessBoard* chessBoard;
	class GameMode* gameMode;


	void HandleInput() override;

	bool isMouseInChessBoard(sf::Vector2i& mousePos, sf::Vector2i& chessBoardStartPos, sf::Vector2i& gamePromptEndPos);

	void calculateHoveredTilePosition(sf::Vector2i& mousePos, sf::Vector2i& chessBoardStartPos);

	void Update() override;

	void Draw() override;

	void Run() override;

	void InnitGUI();

	void loadTextures();
};



