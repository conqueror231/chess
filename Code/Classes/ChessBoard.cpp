#include "ChessBoard.h"


void ChessBoard::InnitChessBoard()
{
    //black pawns
    for (int i = 0; i < 8; ++i) {
        ChessPieces.push_back(new Pawn(sf::Vector2i{ i, 1 }, false));
    }
    //white pawns
    for (int i = 0; i < 8; ++i) {
        ChessPieces.push_back(new Pawn(sf::Vector2i{ i, 6 }, true));
    }

}

const std::vector<ChessPiece*>& ChessBoard::getChessPieces() const
{
    return ChessPieces;
}

ChessPiece* ChessBoard::getChessPieceByPos(int x, int y) const
{
    for (ChessPiece* piece : ChessPieces)
    {
        if (piece->GetPosition().x == x && piece->GetPosition().y == y) {
            return piece;
        }
    }

    return nullptr;
}

bool ChessBoard::removeChessPiece(ChessPiece& chessPieceForDeleting) {
    for (auto it = ChessPieces.begin(); it != ChessPieces.end(); ++it) {
        if (*it == &chessPieceForDeleting) { 
            delete* it; 
            ChessPieces.erase(it); 
            return true;
        }
    }
    return false; 
}

