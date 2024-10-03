#pragma once
#include "Tile.h"

class ChessBoard
{
	Tile* board[8][8];
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

