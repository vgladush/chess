#include "Pawn.h"

Pawn::Pawn(bool player) : IPiece(player, Name::pawn) {}

Pawn::~Pawn() {}

bool Pawn::move_to(int x, int y, int xp, int yp) const
{
	return (xp == x && ((getPlayer() && (yp - y == 1 || (yp == 6 && y == 4))) ||
		(!getPlayer() && (y - yp== 1 || (yp == 1 && y == 3)))));
}

bool Pawn::to_take(int x, int y, int xp, int yp) const
{
	return ((getPlayer() && yp - y == xp - x == 1) ||
		(!getPlayer() && y - yp == x - xp == 1));
}
