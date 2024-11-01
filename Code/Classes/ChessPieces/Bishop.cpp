#include "Bishop.h"
#include"../ChessBoard.h"
bool Bishop::CanMoveTo(sf::Vector2i newPosition)
{
    if (ChessPiece::CanMoveTo(newPosition) == false)
        return false;

    return true;
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
