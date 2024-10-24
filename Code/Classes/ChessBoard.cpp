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
    // Black Rooks
    ChessPieces.push_back(new Rook(sf::Vector2i{ 0, 0 }, false));
    ChessPieces.push_back(new Rook(sf::Vector2i{ 7, 0 }, false));
    // White Rooks
    ChessPieces.push_back(new Rook(sf::Vector2i{ 7, 7 }, true));
    ChessPieces.push_back(new Rook(sf::Vector2i{ 0, 7 }, true));

    // Black Knights
    ChessPieces.push_back(new Knight(sf::Vector2i{ 1, 0 }, false));
    ChessPieces.push_back(new Knight(sf::Vector2i{ 6, 0 }, false));
    // White Knights
    ChessPieces.push_back(new Knight(sf::Vector2i{ 1, 7 }, true));
    ChessPieces.push_back(new Knight(sf::Vector2i{ 6, 7 }, true));

    // Black bishops
    ChessPieces.push_back(new Bishop(sf::Vector2i{ 2, 0 }, false));
    ChessPieces.push_back(new Bishop(sf::Vector2i{ 5, 0 }, false));

    // White bishops
    ChessPieces.push_back(new Bishop(sf::Vector2i{ 2, 7 }, true));
    ChessPieces.push_back(new Bishop(sf::Vector2i{ 5, 7 }, true));

    // Black Queen 
    ChessPieces.push_back(new Queen(sf::Vector2i{ 3, 0 }, false));

    //White Queen
    ChessPieces.push_back(new Queen(sf::Vector2i{ 3, 7 }, true));

    // Black King 
    ChessPieces.push_back(new King(sf::Vector2i{ 4, 0 }, false));

    // White King 
    ChessPieces.push_back(new King(sf::Vector2i{ 4, 7 }, true));


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

