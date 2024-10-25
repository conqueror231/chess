#include "Queen.h"
#include <iostream>
#include "../ChessBoard.h"
bool Queen::Move(sf::Vector2i newPosition)
{
	if (newPosition.x != this->position.x) {

		if (IsPathClear(Direction::Horizontal, newPosition) == false)
			return false;
	}

	if (newPosition.y != this->position.y) {
		if (IsPathClear(Direction::Vertical, newPosition) == false)
			return false;
	}

	if (std::abs(newPosition.x - this->position.x) == std::abs(newPosition.y - this->position.y))
	{
		if (IsPathClear(Direction::Diagonal, newPosition) == false)
			return false;
		
	}
	this->position = newPosition;
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
