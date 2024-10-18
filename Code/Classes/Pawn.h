#pragma once
#include "ChessPiece.h"
class Pawn : public ChessPiece {
public:
    Pawn(int startX, int startY, bool isWhite) : ChessPiece(startX, startY, isWhite) {}

    bool Move(int newX, int newY, const std::vector<ChessPiece>& pieces) override;
};

