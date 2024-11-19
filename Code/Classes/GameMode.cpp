#include "GameMode.h"
#include <iostream>
#include "ChessBoard.h"

bool GameMode::isCheckmate(bool isWhite)
{
    bool canMove = false;
    for (ChessPiece* piece : ChessBoard::getInstance().getChessPieces()) {
        if (piece->isWhite == isWhite) {  
            for (int x = 0; x < 8; ++x) {
                for (int y = 0; y < 8; ++y) {
                    sf::Vector2i newPosition(x, y);
                    ChessPiece* pieceOnTile = ChessBoard::getInstance().getChessPieceByPos(newPosition.x, newPosition.y);
                    if (pieceOnTile == nullptr) {
                        if (piece->CanMoveTo(newPosition) && !piece->isKingInCheck(newPosition)) {
                            canMove = true;
                            break;
                        }
                    }
                    else {
                        if (pieceOnTile->isWhite == isWhite) {
                            continue; 
                        }
                        else {
                            if (piece->CanAttack(*pieceOnTile) && !piece->isKingInCheck(newPosition, pieceOnTile)) {
                                canMove = true;
                                break;
                            }
                        }
                    }
                }
                if (canMove) break;  
            }
        }
        if (canMove) break;  
    }
    if (!canMove) {
        if (ChessBoard::getInstance().isKingInCheck(!isWhiteTurn) == false)
            return false;
        else
            return true;
    }

    return false; 
}
bool GameMode::isStalemate()
{
    if(isCheckmate(!isWhiteTurn) && ChessBoard::getInstance().isKingInCheck(!isWhiteTurn) == false)
    return true;

    return false;
}

void GameMode::endGame(const std::string& message)
{
    std::cout << message << std::endl;
}

void GameMode::switchTurn()
{
    isWhiteTurn = !isWhiteTurn;
}

bool GameMode::isWhiteTurnNow()
{
    return isWhiteTurn;
}

void GameMode::checkGameState()
{
    if (isCheckmate(!isWhiteTurn) ) {
        endGame(isWhiteTurn ? "White wins by checkmate!" : "Black wins by checkmate!");
  
    }
    else if (isStalemate()) {
        endGame("Stalemate! Draw game.");

    }
    else {
        switchTurn(); 
    }

}

GameState GameMode::getGameState()
{
    if (isCheckmate(!isWhiteTurn)) {
        return GameState::Checkmate;
    }
    if (isStalemate()) {
        return GameState::Stalemate;
    }

    return GameState::InProgress;
}
