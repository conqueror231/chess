#include "Knight.h"
#include "../ChessBoard.h"
bool Knight::Move(sf::Vector2i newPosition)
{

    int dx = std::abs(newPosition.x - this->position.x);
    int dy = std::abs(newPosition.y - this->position.y);

   
    if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2)) {
        this->position = newPosition;
        return true;
    }

    return false;

}

bool Knight::Attack(ChessPiece& targetPiece)
{
    int dx = std::abs(targetPiece.GetPosition().x - this->position.x);
    int dy = std::abs(targetPiece.GetPosition().y - this->position.y);

   
    if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2)) {
        this->position = targetPiece.GetPosition();
        ChessBoard::getInstance().removeChessPiece(targetPiece);
        return true;
    }

    return false;
}
