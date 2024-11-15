#include "King.h"
#include <iostream>
#include "../ChessBoard.h"
#include "../GameLog.h"


bool King::CanMoveTo(sf::Vector2i newPosition)
{
    if (Ñastling(newPosition, true))
    {
        needToCastle = true;
        return true;
    }
    int distanceX = std::abs(newPosition.x - this->position.x);
    int distanceY = std::abs(newPosition.y - this->position.y);

    if ((distanceX == 1 && distanceY == 0) || (distanceX == 0 && distanceY == 1) || (distanceX == 1 && distanceY == 1))
	{
		if (isKingInCheck(newPosition, ChessBoard::getInstance().getChessPieceByPos(newPosition.x, newPosition.y)) ) {
			return false;
		}
        return true;
    }
//	std::cout << "Invalid move" << std::endl;
    return false;
}

bool King::Ñastling(sf::Vector2i newPosition, bool onlyCheckIfCanCastle)
{
    sf::Vector2i closerRookPos = { 7, isWhite ? 7 : 0 };
    sf::Vector2i furtherRookPos = { 0, isWhite ? 7 : 0 };


    if (newPosition == sf::Vector2i{ closerRookPos.x - 1, closerRookPos.y }) {

        if (ChessBoard::getInstance().Castling(isWhite, true, onlyCheckIfCanCastle) == false) return false;
 
        GameLog::getInstance().addLog("Short  castling");
        return true;
    }

    if (newPosition == sf::Vector2i{ furtherRookPos.x + 1, furtherRookPos.y })
    {
        if (ChessBoard::getInstance().Castling(isWhite, false, onlyCheckIfCanCastle) == false) return false;
        GameLog::getInstance().addLog("Long  castling");

        return true;
    }


    return false;
}

bool King::Move(sf::Vector2i newPosition)
{
    if (CanMoveTo(newPosition) == false) {
        return false;
    }

    if (needToCastle) {
        if (Ñastling(newPosition)) return true;
        else return false;
    }
 
    if (isKingInCheck(newPosition))
        return false;

    isFirstMove = false;
    this->position = newPosition;
    return true;

}

bool King::getIsFirstMove() const {
    return isFirstMove;
}
