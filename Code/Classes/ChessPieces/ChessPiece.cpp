#include "ChessPiece.h"
#include "iostream"
#include "../ChessBoard.h"
#include "../GameLog.h"

bool ChessPiece::IsPathClear(Direction dir, sf::Vector2i targetPos)
{
    if (dir == Direction::Horizontal) {
		std::vector<sf::Vector2i> positions = ChessBoard::getInstance().
			getPositionsOfAllPiecesOnDirection(Direction::Horizontal, this->position);
		if (targetPos.x > this->position.x) {
			int closestPos = 7;
			for (sf::Vector2i pos : positions) {
				if (pos.x < closestPos && pos.x > this->position.x && pos.x != this->position.x)
					closestPos = pos.x;
			}
			if (targetPos.x > closestPos) {
				//std::cout << "Another Figure on the way" << std::endl;
				return false;
			}
		}
		if (targetPos.x < this->position.x) {
			int closestPos = 0;
			for (sf::Vector2i pos: positions) {
				if (pos.x > closestPos && pos.x < this->position.x && pos.x != this->position.x)
					closestPos = pos.x;
			}
			if (targetPos.x < closestPos) {
				//std::cout << "Another Figure on the way" << std::endl;
				return false;
			}
		}

    }
	if (dir == Direction::Vertical) {
		
			std::vector<sf::Vector2i> positions = ChessBoard::getInstance().
				getPositionsOfAllPiecesOnDirection(Direction::Vertical, this->position);

			if (targetPos.y > this->position.y) {
				int closestPos = 7;
				for (sf::Vector2i pos : positions) {
					if (pos.y < closestPos && pos.y > this->position.y && pos.y != this->position.y)
						closestPos = pos.y;
				}
				if (targetPos.y > closestPos) {
					//std::cout << "Another Figure on the way" << std::endl;
					return false;
				}
			}
			if (targetPos.y < this->position.y) {
				int closestPos = 0;
				for (sf::Vector2i pos : positions) {
					if (pos.y > closestPos && pos.y < this->position.y && pos.y != this->position.y)
						closestPos = pos.y;
				}
				if (targetPos.y < closestPos) {
					//std::cout << "Another Figure on the way" << std::endl;
					return false;
				}
			}


	}
	if (dir == Direction::Diagonal) {

		int dx = (targetPos.x > this->position.x) ? 1 : -1;
		int dy = (targetPos.y > this->position.y) ? 1 : -1;


		sf::Vector2i checkPos = this->position;


		while (checkPos.x != targetPos.x && checkPos.y != targetPos.y) {
	
			checkPos.x += dx;
			checkPos.y += dy;

			if (checkPos.x < 0 || checkPos.y < 0)
				break;

			if (checkPos.x == targetPos.x && checkPos.y == targetPos.y)
				break;
		
			if (ChessPiece* piece = ChessBoard::getInstance().getChessPieceByPos(checkPos.x, checkPos.y)) {
			
				return false;
			}
		}
	}

    return true;
}
bool ChessPiece::Move(sf::Vector2i newPosition, bool onlyCheckIfCanMove)
{
	if (CanMoveTo(newPosition) == false) {
		return false;
	}
	if (isKingInCheck(newPosition)) {
		return false;
	}
	if (onlyCheckIfCanMove == false) {
		GameLog::getInstance().logPieceMoved(this->position, newPosition);
		this->position = newPosition;
	}
	return true;
}
bool ChessPiece::CanMoveTo(sf::Vector2i newPosition)
{

	bool isHorizontalMove = (newPosition.y == this->position.y);
	bool isVerticalMove = (newPosition.x == this->position.x);
	bool isDiagonalMove = (std::abs(newPosition.x - this->position.x) == std::abs(newPosition.y - this->position.y));

	if ((isHorizontalMove && !canMoveHorizontal) ||
		(isVerticalMove && !canMoveVertical) ||
		(isDiagonalMove && !canMoveDiagonal) ||
		(!isHorizontalMove && !isVerticalMove && !isDiagonalMove)) {
		return false;
	}

	if (isHorizontalMove && !IsPathClear(Direction::Horizontal, newPosition)) return false;
	if (isVerticalMove && !IsPathClear(Direction::Vertical, newPosition)) return false;
	if (isDiagonalMove && !IsPathClear(Direction::Diagonal, newPosition)) return false;


	return true;
}
bool ChessPiece::CanAttack(ChessPiece& targetPiece)
{
	if (this->isWhite == targetPiece.isWhite)
	{
		//std::cout << "Ally piece" << std::endl;

		GameLog::getInstance().addLog("Ally piece");
		return false;
	}

	if (CanMoveTo(targetPiece.GetPosition()) == false) {
		return false;
	}
	return true;
}
bool ChessPiece::CanAttack(sf::Vector2i newPosition)
{
	if (CanMoveTo(newPosition) == false)
		return false;

	if (isKingInCheck(this->position)) {
		return false;
	}

	return true;
}
bool ChessPiece::Attack(ChessPiece& targetPiece, bool onlyCheckIfCanMove)
{
	if (CanAttack(targetPiece) == false) {
		if(onlyCheckIfCanMove == false)
	    GameLog::getInstance().addLog("Can`t attack this piece");
		return false;
	}

	if (isKingInCheck(targetPiece.GetPosition(), &targetPiece)) {
		return false;
	}

	if (onlyCheckIfCanMove == false)
	{
		GameLog::getInstance().logPieceAttack(this->position, targetPiece.GetPosition(), targetPiece.GetType());
		this->position = targetPiece.GetPosition();
		ChessBoard::getInstance().removeChessPiece(targetPiece);
	}
	return true;
}
void ChessPiece::MoveWithoutChecking(sf::Vector2i newPosition)
{
	this->position = newPosition;
}
bool ChessPiece::isKingInCheck(sf::Vector2i newPosition, ChessPiece* exeptionPiece)
{
	sf::Vector2i oldPos = this->position;
	this->position = newPosition;

	if (ChessBoard::getInstance().isKingInCheck(isWhite, exeptionPiece)) {
		this->position = oldPos;
		//std::cout << "king will be in check" << std::endl;
		return true;
	}
	this->position = oldPos;

	return false;
}

