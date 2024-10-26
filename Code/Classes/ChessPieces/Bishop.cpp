#include "Bishop.h"
#include"../ChessBoard.h"
bool Bishop::Move(sf::Vector2i newPosition)
{
    if (ChessPiece::Move(newPosition) == false)
        return false;

    this->position = newPosition;
    return false;
}

bool Bishop::Attack(ChessPiece& targetPiece)
{
    if (isWhite == targetPiece.isWhite)
        return false;

    if (Move(targetPiece.GetPosition()))
    {
        ChessBoard::getInstance().removeChessPiece(targetPiece);
        return true;
    }
    return false;
}
