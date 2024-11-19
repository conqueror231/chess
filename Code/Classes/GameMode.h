#pragma once

#include <string>

enum  GameState {
	InProgress,
	Checkmate,
	Stalemate
};
class GameMode
{
private:
	bool isWhiteTurn = true;

	bool isCheckmate(bool isWhite);
	bool isStalemate();
	void endGame(const std::string& message);
	void switchTurn();
public:
	bool isWhiteTurnNow();
	void checkGameState();
	GameState getGameState();
};

