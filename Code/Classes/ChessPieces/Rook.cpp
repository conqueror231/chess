#include "Rook.h"
#include "../ChessBoard.h"
#include <iostream>
#include"vector"
#include"../Direction.h"
bool Rook::Move(sf::Vector2i newPosition)
{
	if(newPosition.y != this->position.y && newPosition.x != this->position.x)
	return false;

	if (newPosition.x != this->position.x) {

		if (IsPathClear(Direction::Horizontal, newPosition) == false)
			return false;
	}
    
	if (newPosition.y != this->position.y) {
		if (IsPathClear(Direction::Vertical, newPosition) == false)
			return false;
	}

    this->position = newPosition;
    return true;
	
}

bool Rook::Attack(ChessPiece& targetPiece)
{
	if (this->isWhite == targetPiece.isWhite)
	{
		std::cout << "Ally piece" << std::endl;
		return false;

	}
	if(Move(targetPiece.GetPosition()))
	ChessBoard::getInstance().removeChessPiece(targetPiece);
	
	return true;
}
