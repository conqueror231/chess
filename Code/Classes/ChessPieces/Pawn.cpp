#include "Pawn.h"
#include "iostream"
#include "../ChessBoard.h"

bool Pawn::CanMoveTo(sf::Vector2i newPosition)
{
	int distY = 1;

	if (newPosition.x != this->position.x)
		return false;

	int distanceToNewPos = std::abs(std::abs(newPosition.y) - std::abs(this->GetPosition().y));
	if(distanceToNewPos > distY && isFirstMove == false)
		return false;

	if (isFirstMove && distanceToNewPos > 2) 
		return false;
	

	if (distanceToNewPos == 2 && isFirstMove) {
		int direction = isWhite ? 1 : -1;
		if (ChessBoard::getInstance().IsTileHasFigureOnIt(newPosition.x, newPosition.y + direction)) {
			std::cout << "Figure on the way" << std::endl;
			return false;
		}
	}



	if ((this->position.y < newPosition.y && isWhite) ||
		(this->position.y > newPosition.y && !isWhite))
		return false;

	if (isKingInCheck(newPosition))
		return false;

	isFirstMove = false;
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
		if (isKingInCheck(targetPos))
			return false;
		this->position = targetPos;
		ChessBoard::getInstance().removeChessPiece(targetPiece);
		return true;  
	}

	std::cout << "Can't attack" << std::endl;
	return false;
}
