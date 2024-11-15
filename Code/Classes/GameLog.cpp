#include "GameLog.h"
#include <sstream>
#include "ChessBoard.h"

#include "ChessPieces/ChessPiece.h"

void GameLog::logPieceAttack(sf::Vector2i fromTile, sf::Vector2i toTile, const  PieceType pieceType)
{
    const char columnsLabels[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };

    ChessPiece* piece = ChessBoard::getInstance().getChessPieceByPos(fromTile.x, fromTile.y);
    if (piece == nullptr)
        return;

    std::string pieceName = getPieceNotation(piece->GetType());
    std::string attackedPieceName = getPieceNotation(pieceType);

    std::ostringstream logMessage;
    logMessage << pieceName << " from "
        << columnsLabels[fromTile.x] << (8 - fromTile.y)
        << " captures " << attackedPieceName << " at "
        << columnsLabels[toTile.x] << (8 - toTile.y);

    addLog(logMessage.str());
}

void GameLog::logPieceMoved(sf::Vector2i fromTile, sf::Vector2i toTile)
{ 
    const char columnsLabels[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };

    ChessPiece* piece = ChessBoard::getInstance().getChessPieceByPos(fromTile.x, fromTile.y);
    if (piece == nullptr)
        return;


    std::string pieceName = getPieceNotation(piece->GetType());


    std::ostringstream logMessage;


    logMessage << pieceName
        << columnsLabels[fromTile.x] << (8 - fromTile.y)
        << "-"
        << columnsLabels[toTile.x] << (8 - toTile.y) << ";";


    logMessage << pieceName << " moved from "
        << columnsLabels[fromTile.x] << (8 - fromTile.y)
        << " to "
        << columnsLabels[toTile.x] << (8 - toTile.y) << ".";

    addLog(logMessage.str());
}

void GameLog::addLog(const std::string& logMessage)
{ 
	log = logMessage;
}

const std::string& GameLog::getLog() const
{

	return log;
}

std::string GameLog::getPieceNotation(PieceType type)
{
    switch (type) {
    case PieceType::King:
        return "K";  // Король
    case PieceType::Queen:
        return "Q";  // Ферзь
    case PieceType::Rook:
        return "R";  // Ладья
    case PieceType::Bishop:
        return "B";  // Слон
    case PieceType::Knight:
        return "N";  // Конь
    case PieceType::Pawn:
        return "";   // Пешка без обозначения
    default:
        return "?";  // Неизвестная фигура
    }
}

