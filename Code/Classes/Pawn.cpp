#include "Pawn.h"

bool Pawn::Move(sf::Vector2i newPosition, const std::vector<ChessPiece *>& pieces)
{
	position = newPosition;
	return false;
}
