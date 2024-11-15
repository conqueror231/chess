// GameLog.h
#pragma once
#include <vector>
#include <string>
#include <SFML/System/Vector2.hpp>
#include "ChessPieces/PieceType.h" 
class GameLog {
public:
    static GameLog& getInstance() {
        static GameLog instance;
        return instance;
    }

    void logPieceAttack(sf::Vector2i fromTile, sf::Vector2i toTile, const  PieceType pieceType);
    void logPieceMoved(sf::Vector2i fromTile, sf::Vector2i toTile);

    void addLog(const std::string& logMessage);
    const std::string& getLog() const;

    GameLog(const GameLog&) = delete;
    GameLog& operator=(const GameLog&) = delete;

private:
    std::string getPieceNotation( PieceType type);
    GameLog() {}  
    std::string log = "Game Log";
    const char columnsLabels[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
};
