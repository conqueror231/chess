#pragma once
#include "ChessPieces/ChessPiece.h"
#include "ChessPieces/Pawn.h"
#include "ChessPieces/Rook.h"
#include "ChessPieces/Queen.h"
#include "ChessPieces/King.h"
#include "ChessPieces/Bishop.h"
#include "ChessPieces/Knight.h"
#include"Direction.h"

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
    bool IsTileHasFigureOnIt(int x, int y) const;
    const std::vector<ChessPiece*>& getChessPieces() const;
    ChessPiece* getChessPieceByPos(int x, int y) const;
    bool removeChessPiece(ChessPiece& chessPieceForDeleting);
    std::vector<sf::Vector2i> getPositionsOfAllPiecesOnDirection(Direction dir, sf::Vector2i pos);
    bool isKingInCheck(bool isWhite, ChessPiece* exceptionPiece = nullptr) const; 
    void resetBoard();
    bool canCastling(bool isWhite, bool isShortCastling);
};

