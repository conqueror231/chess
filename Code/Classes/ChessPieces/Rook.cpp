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

		std::vector<int> positions = ChessBoard::getInstance().
			getPositionsOfAllPiecesOnDirection(Direction::Horizontal, this->position);

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
	if (targetPiece.GetPosition().y != this->position.y && targetPiece.GetPosition().x != this->position.x)
		return false;
	this->position = targetPiece.GetPosition();
	ChessBoard::getInstance().removeChessPiece(targetPiece);
	
	return false;
}
