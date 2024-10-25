#pragma once
#include <vector>
#include "PieceType.h"
#include "SFML/System/Vector2.hpp"
#include"../Direction.h"

class ChessPiece {
protected:
    sf::Vector2i position;
    PieceType pieceType;
    bool IsPathClear(Direction dir, sf::Vector2i Position);

public:
    bool isWhite = false;

    ChessPiece(sf::Vector2i startPosition, PieceType pieceType, bool isWhite)
        : position(startPosition), pieceType(pieceType),  isWhite(isWhite) {}

    sf::Vector2i GetPosition() const {
        return position;
    }
    PieceType GetType() const {
        return pieceType;
    }

    virtual bool Move(sf::Vector2i newPosition) = 0; 
    virtual bool Attack(ChessPiece& targetPiece) = 0; 
   

};
