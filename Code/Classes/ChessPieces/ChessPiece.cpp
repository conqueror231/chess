#include "ChessPiece.h"
#include "iostream"
#include "../ChessBoard.h"
bool ChessPiece::IsPathClear(Direction dir, sf::Vector2i targetPos)
{
    if (dir == Direction::Horizontal) {
		std::vector<int> positions = ChessBoard::getInstance().
			getPositionsOfAllPiecesOnDirection(Direction::Horizontal, this->position);
		if (targetPos.x > this->position.x) {
			int closestPos = 7;
			for (int pos : positions) {
				if (pos < closestPos && pos > this->position.x && pos != this->position.x)
					closestPos = pos;
			}
			if (targetPos.x > closestPos) {
				std::cout << "Another Figure on the way" << std::endl;
				return false;
			}
		}
		if (targetPos.x < this->position.x) {
			int closestPos = 0;
			for (int pos : positions) {
				if (pos > closestPos && pos < this->position.x && pos != this->position.x)
					closestPos = pos;
			}
			if (targetPos.x < closestPos) {
				std::cout << "Another Figure on the way" << std::endl;
				return false;
			}
		}

    }

	if (dir == Direction::Vertical) {
		
			std::vector<int> positions = ChessBoard::getInstance().
				getPositionsOfAllPiecesOnDirection(Direction::Vertical, this->position);

			if (targetPos.y > this->position.y) {
				int closestPos = 7;
				for (int pos : positions) {
					if (pos < closestPos && pos > this->position.y && pos != this->position.y)
						closestPos = pos;
				}
				if (targetPos.y > closestPos) {
					std::cout << "Another Figure on the way" << std::endl;
					return false;
				}
			}
			if (targetPos.y < this->position.y) {
				int closestPos = 0;
				for (int pos : positions) {
					if (pos > closestPos && pos < this->position.y && pos != this->position.y)
						closestPos = pos;
				}
				if (targetPos.y < closestPos) {
					std::cout << "Another Figure on the way" << std::endl;
					return false;
				}
			}


	}
	
	if (dir == Direction::Diagonal) {

	}
    return true;
}
