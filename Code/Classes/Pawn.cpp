#include "Pawn.h"
#include "iostream"
#include"ChessBoard.h"

bool Pawn::Move(sf::Vector2i newPosition)
{
	position = newPosition;
	return true;
}

bool Pawn::Attack(ChessPiece& targetPiece)
{
	int distX = 1;
	int distY = 1;
	if (this->isWhite == targetPiece.isWhite)
	{
		std::cout << "Ally piece" << std::endl;
		return false;

	}
	sf::Vector2i targetPos = targetPiece.GetPosition();
	int dir = isWhite ? -1 : 1;
	if ((targetPos.x == this->position.x + distX || targetPos.x == this->position.x - distX) &&
		targetPos.y == this->position.y + distY * dir)
	{
		this->position = targetPos;
	
		ChessBoard::getInstance().removeChessPiece(targetPiece);
		return true;  
	}

	std::cout << "Can't attack" << std::endl;
	return false;
}
