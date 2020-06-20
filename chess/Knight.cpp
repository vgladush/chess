#include "Knight.h"

Knight::Knight(bool player) : IPiece(player, Name::knight) {}

Knight::~Knight() {}

bool Knight::move_to(Coord& cd) const
{
	return ((abs(cd.i - cd.x) == 2 && abs(cd.j - cd.y) == 1) ||
		(abs(cd.i - cd.x) == 1 && abs(cd.j - cd.y) == 2));
}

bool Knight::to_take(Coord& cd) const
{
	return move_to(cd);
}
