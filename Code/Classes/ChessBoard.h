#pragma once
#include "ChessPiece.h"
#include "Pawn.h"

class ChessBoard
{
	std::vector<ChessPiece*> ChessPieces;
	float TileSize = 50.f;

    void InnitChessBoard();


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
    const std::vector<ChessPiece*>& getChessPieces() const;
    ChessPiece* getChessPieceByPos(int x, int y) const;
    bool removeChessPiece(ChessPiece& chessPieceForDeleting);
};

