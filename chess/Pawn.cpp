#include "Pawn.h"

Pawn::Pawn() {}

Pawn::~Pawn() {}

bool Pawn::move_to(int x, int y) const
{
	return ((getPlayer() && (y - getY() == 1 || (getY() == 6 && y == 4))) ||
		(!getPlayer() && (getY() - y == 1 || (getY() == 1 && y == 3))));
}
