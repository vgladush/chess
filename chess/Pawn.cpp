#include "Pawn.h"

Pawn::Pawn() {}

Pawn::~Pawn() {}

bool Pawn::move_to(int x, int y) const
{
	return (getX() == x && ((getPlayer() && (getY() - y == 1 || (getY() == 6 && y == 4))) ||
		(!getPlayer() && (y - getY()== 1 || (getY() == 1 && y == 3)))));
}

bool Pawn::to_take(int x, int y) const
{
	return ((getPlayer() && getY() - y == getX() - x == 1) ||
		(!getPlayer() && y - getY() == x - getX() == 1));
}
