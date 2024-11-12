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

    bool canMoveHorizontal = false;
    bool canMoveVertical = false;
    bool canMoveDiagonal = false;


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
    bool isKingInCheck(sf::Vector2i newPosition, ChessPiece* exceptionPiece = nullptr);
    virtual bool Move(sf::Vector2i newPosition);
    virtual bool CanMoveTo(sf::Vector2i newPosition);
    virtual bool CanAttack(ChessPiece& targetPiece);
    virtual bool Attack(ChessPiece& targetPiece); 
    void MoveWithoutChecking(sf::Vector2i newPosition);

};
