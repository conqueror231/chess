#include "Queen.h"
#include <iostream>
#include "../ChessBoard.h"
bool Queen::CanMoveTo(sf::Vector2i newPosition)
{
	if (ChessPiece::CanMoveTo(newPosition) == false)
		return false;

    return true;
}
bool Queen::Attack(ChessPiece& targetPiece)
{
	if (this->isWhite == targetPiece.isWhite)
	{
		std::cout << "Ally piece" << std::endl;
		return false;

	}
	if (Move(targetPiece.GetPosition()))
		ChessBoard::getInstance().removeChessPiece(targetPiece);


    return true;
}
