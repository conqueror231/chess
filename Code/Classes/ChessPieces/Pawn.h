#pragma once
#include "ChessPiece.h"

class Pawn : public ChessPiece {
private:
    bool isFirstMove = true;

public:
    Pawn(sf::Vector2i startPosition, PieceType pieceType, bool isWhite)
        : ChessPiece(startPosition, pieceType, isWhite) {}

    bool CanMoveTo(sf::Vector2i newPosition) override;
    bool CanAttack(ChessPiece& targetPiece) override;
    bool NeedToPromote();
    bool Move(sf::Vector2i newPosition, bool onlyCheckIfCanMove) override;
    bool Attack(ChessPiece& targetPiece, bool onlyCheckIfCanMove = false)override;
};
