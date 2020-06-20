#include "Queen.h"

Queen::Queen(bool player) : IPiece(player, Name::queen) {}

Queen::~Queen() {}

bool Queen::move_to(Coord& cd) const
{
	return (abs(cd.i - cd.x) == abs(cd.j - cd.y)
		|| cd.i == cd.x || cd.j == cd.y);
}

bool Queen::to_take(Coord& cd) const
{
	return move_to(cd);
}
