#pragma once
#include "ChessPiece.h"
class Bishop :
    public ChessPiece
{
public:
    Bishop(sf::Vector2i startPosition, PieceType pieceType, bool isWhite)
        : ChessPiece(startPosition, pieceType, isWhite) {}

    bool Move(sf::Vector2i newPosition) override;
    bool Attack(ChessPiece& targetPiece) override;
};

