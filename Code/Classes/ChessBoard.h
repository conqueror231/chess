#pragma once
#include "ChessPiece.h"

class ChessBoard
{
	std::vector<ChessPiece> ChessPieces;
	float TileSize = 50.f;



    ChessBoard(const ChessBoard&) = delete;
    ChessBoard& operator=(const ChessBoard&) = delete;

public:
    ChessBoard() {};

    static ChessBoard& getInstance() {
        
        static ChessBoard instance;
        return instance;
    }


   
};

