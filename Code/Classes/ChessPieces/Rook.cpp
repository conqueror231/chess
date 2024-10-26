#include "Rook.h"
#include "../ChessBoard.h"
#include <iostream>
#include"vector"
#include"../Direction.h"
bool Rook::Move(sf::Vector2i newPosition)
{
	if (ChessPiece::Move(newPosition) == false)
		return false;


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
