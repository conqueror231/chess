#include "ChessBoard.h"
#include "ChessPieces/ChessPiece.h"
#include "ChessPieces/PieceType.h"

void ChessBoard::InnitChessBoard()
{

    //black pawns
    for (int i = 0; i < 8; ++i) {
        ChessPieces.push_back(new Pawn(sf::Vector2i{ i, 1 }, PieceType::Pawn, false));
    }
    //white pawns
    for (int i = 0; i < 8; ++i) {
        ChessPieces.push_back(new Pawn(sf::Vector2i{ i, 6 }, PieceType::Pawn, true));
    }
    // Black Rooks
    ChessPieces.push_back(new Rook(sf::Vector2i{ 0, 0 }, PieceType::Rook, false));
    ChessPieces.push_back(new Rook(sf::Vector2i{ 7, 0 }, PieceType::Rook, false));
    // White Rooks
    ChessPieces.push_back(new Rook(sf::Vector2i{ 7, 7 }, PieceType::Rook, true));
    ChessPieces.push_back(new Rook(sf::Vector2i{ 0, 7 }, PieceType::Rook, true));

    // Black Knights
    ChessPieces.push_back(new Knight(sf::Vector2i{ 1, 0 }, PieceType::Knight, false));
    ChessPieces.push_back(new Knight(sf::Vector2i{ 6, 0 }, PieceType::Knight, false));
    // White Knights
    ChessPieces.push_back(new Knight(sf::Vector2i{ 1, 7 }, PieceType::Knight, true));
    ChessPieces.push_back(new Knight(sf::Vector2i{ 6, 7 }, PieceType::Knight, true));

    // Black bishops
    ChessPieces.push_back(new Bishop(sf::Vector2i{ 2, 0 }, PieceType::Bishop, false));
    ChessPieces.push_back(new Bishop(sf::Vector2i{ 5, 0 }, PieceType::Bishop, false));

    // White bishops
    ChessPieces.push_back(new Bishop(sf::Vector2i{ 2, 7 }, PieceType::Bishop, true));
    ChessPieces.push_back(new Bishop(sf::Vector2i{ 5, 7 }, PieceType::Bishop, true));

    // Black Queen 
    ChessPieces.push_back(new Queen(sf::Vector2i{ 3, 0 }, PieceType::Queen, false));

    //White Queen
    ChessPieces.push_back(new Queen(sf::Vector2i{ 3, 7 }, PieceType::Queen, true));

    // Black King 
    ChessPieces.push_back(new King(sf::Vector2i{ 4, 0 }, PieceType::King, false));

    // White King 
    ChessPieces.push_back(new King(sf::Vector2i{ 4, 7 }, PieceType::King, true));


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

