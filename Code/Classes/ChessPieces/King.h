#pragma once
#include "ChessPiece.h"
class King :
    public ChessPiece
{
public:
    King(sf::Vector2i startPosition, PieceType pieceType, bool isWhite)
        : ChessPiece(startPosition, pieceType, isWhite) {}
    bool CanMoveTo(sf::Vector2i newPosition) override;
};
