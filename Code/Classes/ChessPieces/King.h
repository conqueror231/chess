#pragma once
#include "ChessPiece.h"
class King :
    public ChessPiece
{
private: 
    bool isFirstMove = true;
    bool needToCastle = false;

public:
    bool getIsFirstMove() const;
    King(sf::Vector2i startPosition, PieceType pieceType, bool isWhite)
        : ChessPiece(startPosition, pieceType, isWhite) {}
    bool CanMoveTo(sf::Vector2i newPosition) override;
    bool Ñastling(sf::Vector2i newPosition, bool onlyCheckIfCanCastle = false);
    bool Move(sf::Vector2i newPosition, bool onlyCheckIfCanMove) override;
    bool CanMoveForHint(sf::Vector2i newPosition);
};
