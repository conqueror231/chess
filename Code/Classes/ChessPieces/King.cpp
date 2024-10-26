#include "King.h"
#include <iostream>
#include "../ChessBoard.h"
bool King::Move(sf::Vector2i newPosition)
{

    int distanceX = std::abs(newPosition.x - this->position.x);
    int distanceY = std::abs(newPosition.y - this->position.y);

    if ((distanceX == 1 && distanceY == 0) || (distanceX == 0 && distanceY == 1) || (distanceX == 1 && distanceY == 1))
    {
        this->position = newPosition;
        return true;
    }

	std::cout << "Invalid move" << std::endl;
    return false;
}

bool King::Attack(ChessPiece& targetPiece)
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
