#pragma once

#include <string>
class GameMode
{
private:
	bool isWhiteTurn = true;
	int whiteTime = 300;      
	int blackTime = 300;
	bool isCheckmate(bool isWhite);
	bool isStalemate();
	void endGame(const std::string& message);
	void switchTurn();
public:
	bool isWhiteTurnNow();
	void checkGameState();
	
};

