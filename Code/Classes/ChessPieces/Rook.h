#pragma once
#include "ChessPiece.h"
class Rook :
    public ChessPiece
{
private:
bool isFirstMove = true;

public:
    bool getIsFirstMove() const;

    Rook(sf::Vector2i startPosition, PieceType pieceType, bool isWhite)
        : ChessPiece(startPosition, pieceType, isWhite) {
        canMoveHorizontal = true;
        canMoveVertical = true;
    }


};

