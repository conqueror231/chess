#pragma once
#include <vector>

#include "SFML/System/Vector2.hpp"

class ChessPiece {
protected:
    sf::Vector2i position;


public:
    bool isWhite = false;

    ChessPiece(sf::Vector2i startPosition, bool isWhite)
        : position(startPosition), isWhite(isWhite) {} 

    sf::Vector2i GetPosition() const {
        return position;
    }

    virtual bool Move(sf::Vector2i newPosition) = 0; 
    virtual bool Attack(ChessPiece& targetPiece) = 0; 
};
