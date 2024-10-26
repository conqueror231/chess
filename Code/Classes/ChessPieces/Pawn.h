#pragma once
#include "ChessPiece.h"

class Pawn : public ChessPiece {
private:
    bool isFirstMove;

public:
    Pawn(sf::Vector2i startPosition, PieceType pieceType, bool isWhite)
        : ChessPiece(startPosition, pieceType, isWhite) {}

    bool Move(sf::Vector2i newPosition) override;
    bool Attack(ChessPiece& targetPiece) override;
};
