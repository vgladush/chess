#include "King.h"

King::King(bool player) : IPiece(player, Name::king) {}

King::~King() {}

bool King::move_to(Coord& cd) const
{
	return (abs(cd.i - cd.x) <= 1 && abs(cd.j - cd.y) <= 1);
}

bool King::to_take(Coord& cd) const
{
	return move_to(cd);
}
