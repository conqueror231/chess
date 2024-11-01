#include "Rook.h"
#include "../ChessBoard.h"
#include <iostream>
#include"vector"
#include"../Direction.h"
bool Rook::CanMoveTo(sf::Vector2i newPosition)
{
	if (ChessPiece::CanMoveTo(newPosition) == false)
		return false;


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
