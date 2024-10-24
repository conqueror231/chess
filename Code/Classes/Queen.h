#pragma once
#include "ChessPiece.h"
class Queen :
    public ChessPiece
{
public:
    Queen(sf::Vector2i startPosition, bool isWhite)
        : ChessPiece(startPosition, isWhite) {}

    bool Move(sf::Vector2i newPosition) override;
    bool Attack(ChessPiece& targetPiece) override;
};

