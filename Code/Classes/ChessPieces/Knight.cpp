#include "Knight.h"
#include "../ChessBoard.h"
bool Knight::CanMoveTo(sf::Vector2i newPosition)
{
    int dx = std::abs(newPosition.x - this->position.x);
    int dy = std::abs(newPosition.y - this->position.y);

    if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2)) {
     
        return true;
    }

    return false;

}
