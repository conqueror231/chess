#include "ChessPiece.h"
#include "iostream"
#include "../ChessBoard.h"
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
				std::cout << "Another Figure on the way" << std::endl;
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
				std::cout << "Another Figure on the way" << std::endl;
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
					std::cout << "Another Figure on the way" << std::endl;
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
					std::cout << "Another Figure on the way" << std::endl;
					return false;
				}
			}


	}
	
	if (dir == Direction::Diagonal) {
		
		std::vector<sf::Vector2i> positions = ChessBoard::getInstance().
			getPositionsOfAllPiecesOnDirection(Direction::Diagonal, this->position);

		int dx = (targetPos.x > this->position.x) ? 1 : -1;
		int dy = (targetPos.y > this->position.y) ? 1 : -1;
		sf::Vector2i checkPos = this->position;


		while ((checkPos.x += dx) != targetPos.x && (checkPos.y += dy) != targetPos.y) {
			if (std::find(positions.begin(), positions.end(), checkPos) != positions.end()) {
				std::cout << "Another Figure on the way diagonally" << std::endl;
				return false;
			}
		}
	}
	

    return true;
}




bool ChessPiece::Move(sf::Vector2i newPosition)
{

	bool isHorizontalMove = (newPosition.y == this->position.y);
	bool isVerticalMove = (newPosition.x == this->position.x);
	bool isDiagonalMove = (std::abs(newPosition.x - this->position.x) == std::abs(newPosition.y - this->position.y));

	if ((isHorizontalMove && !canMoveHorizontal) ||
		(isVerticalMove && !canMoveVertical) ||
		(isDiagonalMove && !canMoveDiagonal)) {
		std::cout << "Invalid move for this piece" << std::endl;
		return false;
	}
	if (isHorizontalMove == false && isVerticalMove == false && isDiagonalMove == false) {
		std::cout << "Invalid move for this piece" << std::endl;
		return false;
	}

	if (isHorizontalMove && !IsPathClear(Direction::Horizontal, newPosition))
		return false;
	if (isVerticalMove && !IsPathClear(Direction::Vertical, newPosition))
		return false;
	if (isDiagonalMove && !IsPathClear(Direction::Diagonal, newPosition))
		return false;

	this->position = newPosition;
	return true;
}
