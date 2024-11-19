#include "Rook.h"
#include "../ChessBoard.h"
#include <iostream>
#include"vector"
#include"../Direction.h"

bool Rook::getIsFirstMove() const {
    return isFirstMove;
}

bool Rook::Move(sf::Vector2i newPosition, bool onlyCheckIfCanMove)
{
    if (ChessPiece::Move(newPosition, onlyCheckIfCanMove))
    {
        isFirstMove = false;
        return true;
    }
    return false;
}

