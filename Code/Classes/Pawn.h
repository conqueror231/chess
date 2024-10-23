#pragma once
#include "ChessPiece.h"

class Pawn : public ChessPiece {
public:
    Pawn(sf::Vector2i startPosition, bool isWhite) 
        : ChessPiece(startPosition, isWhite) {}

    bool Move(sf::Vector2i newPosition) override;
    bool Attack(ChessPiece& targetPiece) override;
};
