#include "Pawn.h"
#include <iostream>
Pawn::Pawn(bool player) : IPiece(player, Name::pawn) {}

Pawn::~Pawn() {}

bool Pawn::move_to(int x, int y, int xp, int yp) const
{
	return (xp == x && ((getPlayer() && (y - yp == 1 || (y == 6 && yp == 4))) ||
		(!getPlayer() && (yp - y == 1 || (y == 1 && yp == 3)))));
}

bool Pawn::to_take(int x, int y, int xp, int yp) const
{
	return ((getPlayer() && y - yp == 1 && abs(x - xp) == 1) ||
		(!getPlayer() && yp - y == 1 && abs(xp - x) == 1));
}
