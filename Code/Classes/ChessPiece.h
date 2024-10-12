#pragma once
#include<vector>
class ChessPiece {
public:
    int x, y; 
    bool isWhite = false; 

    ChessPiece(int startX, int startY, bool isWhite) : x(startX), y(startY), isWhite(isWhite) {}

    virtual bool Move(int newX, int newY, const std::vector<ChessPiece>& pieces) = 0; 
};
