#include "Rook.h"
#include "ChessBoard.h"
bool Rook::Move(sf::Vector2i newPosition)
{
	if(newPosition.y != this->position.y && newPosition.x != this->position.x)
	return false;

	this->position = newPosition;
	return true;
}

bool Rook::Attack(ChessPiece& targetPiece)
{
	if (targetPiece.GetPosition().y != this->position.y && targetPiece.GetPosition().x != this->position.x)
		return false;
	this->position = targetPiece.GetPosition();
	ChessBoard::getInstance().removeChessPiece(targetPiece);
	
	return false;
}
