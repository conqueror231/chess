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

	const uint16_t offsetXForChessBoard = 75;
	const uint16_t offsetYForChessBoard = 75;
	const uint16_t TileSize = 75;

	static const sf::Vector2f TURN_LABEL_FOR_BLACK_POSITION;
	static const sf::Vector2f TURN_LABEL_FOR_WHITE_POSITION;
	static const sf::Vector2f BLACK_KING_COUNTER_POSITION;
	static const sf::Vector2f WHITE_KING_COUNTER_POSITION;
	static const sf::Vector2f GAME_LOG_OUTPUT_POSITION;


	sf::Vector2i hoveredTileIndexes{ -1, -1 };
	sf::Vector2i selectedTileIndexes{ -1, -1 };


	class ChessBoard* chessBoard;
	class GameMode* gameMode;
	class GameLog* gameLog;

	void HandleInput() override;

	bool isMouseInChessBoard(sf::Vector2i& mousePos, sf::Vector2i& chessBoardStartPos, sf::Vector2i& gamePromptEndPos);

	void calculateHoveredTilePosition(sf::Vector2i& mousePos, sf::Vector2i& chessBoardStartPos);


	void Draw() override;

	void Run() override;

	void InnitGUI();

	void loadTextures();
};



