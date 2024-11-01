#include "King.h"
#include <iostream>
#include "../ChessBoard.h"
bool King::CanMoveTo(sf::Vector2i newPosition)
{

    int distanceX = std::abs(newPosition.x - this->position.x);
    int distanceY = std::abs(newPosition.y - this->position.y);

    if ((distanceX == 1 && distanceY == 0) || (distanceX == 0 && distanceY == 1) || (distanceX == 1 && distanceY == 1))
	{
		if (isKingInCheck(newPosition)) {
			return false;
		}
        return true;
    }

	std::cout << "Invalid move" << std::endl;
    return false;
}


