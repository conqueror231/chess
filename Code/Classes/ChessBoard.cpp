#include "ChessBoard.h"
#include "ChessPieces/ChessPiece.h"
#include "ChessPieces/PieceType.h"
#include "iostream"
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

bool ChessBoard::IsTileHasFigureOnIt(int x, int y) const {

    for (ChessPiece* piece : ChessPieces)
    {
        if (piece->GetPosition().x == x && piece->GetPosition().y == y) {
            return true;
        }
    }
    return false;
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
            capturedPieces.push_back(std::make_pair(chessPieceForDeleting.GetType(), chessPieceForDeleting.isWhite));

            delete* it;
            ChessPieces.erase(it);

            return true;
        }
    }
    return false;
}

std::vector<sf::Vector2i> ChessBoard::getPositionsOfAllPiecesOnDirection(Direction dir, sf::Vector2i innitPos)
{
    std::vector<sf::Vector2i> positions{};
    if (dir == Direction::Horizontal)
    {
        for (ChessPiece* piece : ChessPieces)
        {
            if (piece->GetPosition().y == innitPos.y) {
                positions.push_back(piece->GetPosition());

            }
        }
        return positions;
    }
    if (dir == Direction::Vertical)
    {
        for (ChessPiece* piece : ChessPieces)
        {
            if (piece->GetPosition().x == innitPos.x) {
                positions.push_back(piece->GetPosition());

            }
        }
    return positions;
        }
    if (dir == Direction::Diagonal) {
            for (ChessPiece* piece : ChessPieces) {
                int dx = abs(piece->GetPosition().x - innitPos.x);
                int dy = abs(piece->GetPosition().y - innitPos.y);
                if (dx == dy) {
                    positions.push_back(piece->GetPosition());
                }
            }
            return positions;
        }

}

bool ChessBoard::isKingInCheck(bool isWhite, ChessPiece* exceptionPiece) const {
    ChessPiece* king = nullptr;
    for (ChessPiece* piece : ChessPieces) {
        if (piece->GetType() == PieceType::King && piece->isWhite == isWhite) {
            king = piece;
            break;
        }
    }

    if (king) {
        for (ChessPiece* piece : ChessPieces) {
            if (piece == exceptionPiece) continue;
            if (piece->isWhite != isWhite && piece->CanAttack(*king)) {
                return true;
            }
        }
    }
    return false;
}

void ChessBoard::resetBoard() {
    for (auto piece : ChessPieces) {
        delete piece; 
    }
    ChessPieces.clear();

    InnitChessBoard();
}

bool ChessBoard::Castling(bool isWhite, bool isShortCastling, bool onlyCheckIfCanCastle)
{
 
    int y = isWhite ? 7 : 0;
    sf::Vector2i closerRookPos = { 7, y };
    sf::Vector2i furtherRookPos = { 0, y };
    sf::Vector2i startKingPos = { 4, y };

    ChessPiece* ChessPieceOnKingPos = getChessPieceByPos(startKingPos.x, startKingPos.y);
    if (ChessPieceOnKingPos == nullptr)   return false;
    King* kingPiece;
    if ((kingPiece = dynamic_cast<King*>(ChessPieceOnKingPos)) == nullptr) return false;
    if (!kingPiece->getIsFirstMove()) return false;
    if (isKingInCheck(isWhite)) return false;

    sf::Vector2i rookPos = isShortCastling ? closerRookPos : furtherRookPos;
    ChessPiece* ChessPieceOnRookPos = getChessPieceByPos(rookPos.x, rookPos.y);
    if (ChessPieceOnRookPos == nullptr)   return false;
    Rook* rookPiece;
    if ((rookPiece = dynamic_cast<Rook*>(ChessPieceOnRookPos)) == nullptr) return false;
    if (!rookPiece->getIsFirstMove()) return false;

     int step = isShortCastling ? +1 : -1;
     int newXPos = startKingPos.x + step;
    while (true) {
    

        if (ChessPiece* chessPiece = getChessPieceByPos(newXPos, startKingPos.y)) {
            if (chessPiece->GetType() == PieceType::King) break;
            else {
                if (chessPiece->GetType() == PieceType::Rook) break;

                //std::cout << "Figure on the Way" << std::endl;
                return false;
            }
        }
        

        for (ChessPiece* piece : ChessPieces) {
            if (piece->isWhite != isWhite) { 
                if (piece->CanAttack(sf::Vector2i(newXPos, startKingPos.y))) {
                    std::cout << "Cant castle" << std::endl;
                    return false;
                }
            }
        }

        newXPos += step;

        if (newXPos < 0 || newXPos > 7) {
            std::cout << "Out of bounds" << std::endl;
            return false;
        }
    }



    sf::Vector2i newKingPos = { isShortCastling ? rookPos.x - 1 : rookPos.x + 1, rookPos.y };
    sf::Vector2i newRookPos = { isShortCastling ? rookPos.x - 2 : rookPos.x + 2, rookPos.y };

    if (onlyCheckIfCanCastle == false) {
        kingPiece->MoveWithoutChecking(newKingPos);
        rookPiece->MoveWithoutChecking(newRookPos);
    }
    std::cout << "Can Castle" << std::endl;
    return true;
}

void ChessBoard::PromotePawn(Pawn& pawnToPromote)
{

    if (pawnToPromote.isWhite == true)
        ChessPieces.push_back(new Queen(pawnToPromote.GetPosition(), PieceType::Queen, true));
    else
        ChessPieces.push_back(new Queen(pawnToPromote.GetPosition(), PieceType::Queen, false));

    removeChessPiece(pawnToPromote);
}

std::vector<std::pair<PieceType, bool>> ChessBoard::GetCapturedPiecesTypes()
{
    return capturedPieces;
}

std::vector<sf::Vector2i> ChessBoard::getAllPositionsWherePieceCanMove(ChessPiece* piece)
{
    std::vector<sf::Vector2i> positions;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (King* king = dynamic_cast<King*>(piece)) {
                if (king->CanMoveTo(sf::Vector2i(x, y))) {
                    if (IsTileHasFigureOnIt(x, y) == false) {
                        positions.push_back(sf::Vector2i(x, y));
                    }
                }
                if (ChessPiece* pieceForTaking = getChessPieceByPos(x, y)) {
                    if (king->Attack(*pieceForTaking, true)) {
                        positions.push_back(sf::Vector2i(x, y));
                    }
                }

            }
            else {
                if (piece->Move(sf::Vector2i(x, y), true)) {
                    if (IsTileHasFigureOnIt(x, y) == false) {
                        positions.push_back(sf::Vector2i(x, y));
                    }
                }
                if (ChessPiece* pieceForTaking = getChessPieceByPos(x, y)) {
                    if (piece->Attack(*pieceForTaking, true)) {
                        positions.push_back(sf::Vector2i(x, y));
                    }
                }
                

            }
        }
    }
    return positions;
}

