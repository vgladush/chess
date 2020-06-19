#include "Queen.h"

Queen::Queen(bool player) : IPiece(player, Name::queen) {}

Queen::~Queen() {}

bool Queen::move_to(int x, int y, int xp, int yp) const
{
	return (abs(xp - x) == abs(yp - y)
		|| xp == x || yp == y);
}

bool Queen::to_take(int x, int y, int xp, int yp) const
{
	return (abs(xp - x) == abs(yp - y)
		|| xp == x || yp == y);
}
