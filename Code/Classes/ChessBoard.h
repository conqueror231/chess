#pragma once
#include "ChessPiece.h"
#include "Pawn.h"
class ChessBoard
{
	std::vector<ChessPiece*> ChessPieces;
	float TileSize = 50.f;

    void InnitChessBoard() {
        //black pawns
        for (int i = 0; i < 8; ++i) {
            ChessPieces.push_back(new Pawn(i, 1, false));
        }
        //white pawns
        for (int i = 0; i < 8; ++i) {

            ChessPieces.push_back(new Pawn(i, 6, true));
        }
    }


    ChessBoard(const ChessBoard&) = delete;
    ChessBoard& operator=(const ChessBoard&) = delete;

public:
    ChessBoard() {
        InnitChessBoard();
    };

    static ChessBoard& getInstance() {
        
        static ChessBoard instance;
        return instance;
    }
    const std::vector<ChessPiece*>& getChessPieces() const {
        return ChessPieces;
    }

   
};

