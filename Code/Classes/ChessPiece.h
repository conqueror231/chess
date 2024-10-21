#pragma once
#include<vector>
#include <SFML/System/Vector2.hpp>

class ChessPiece {
protected:
    sf::Vector2i position;
 
public:
    sf::Vector2i GetPosition() {
        return position;
    }
    bool isWhite = false; 

    ChessPiece(sf::Vector2i  startPosition, bool isWhite) : position(startPosition), isWhite(isWhite) {}

    virtual bool Move(sf::Vector2i  newPosition, const std::vector<ChessPiece*>& pieces) = 0;
};
