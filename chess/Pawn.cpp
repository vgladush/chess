#include "Pawn.h"
#include <iostream>
Pawn::Pawn(bool player) : IPiece(player, Name::pawn) {}

Pawn::~Pawn() {}

bool Pawn::move_to(Coord& cd) const
{
	return (cd.i == cd.x && ((getPlayer() && (cd.y - cd.j == 1 || (cd.y == 6 && cd.j == 4))) ||
		(!getPlayer() && (cd.j - cd.y == 1 || (cd.y == 1 && cd.j == 3)))));
}

bool Pawn::to_take(Coord& cd) const
{
	return ((getPlayer() && cd.y - cd.j == 1 && abs(cd.x - cd.i) == 1) ||
		(!getPlayer() && cd.j - cd.y == 1 && abs(cd.i - cd.x) == 1));
}
