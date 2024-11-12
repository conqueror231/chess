#include "Rook.h"
#include "../ChessBoard.h"
#include <iostream>
#include"vector"
#include"../Direction.h"

bool Rook::getIsFirstMove() const {
    return isFirstMove;
}

bool Rook::Move(sf::Vector2i newPosition)
{
    if (ChessPiece::Move(newPosition))
    {
        isFirstMove = false;
        return true;
    }
    return false;
}

