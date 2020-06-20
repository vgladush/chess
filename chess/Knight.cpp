#include "Knight.h"

Knight::Knight(bool player) : IPiece(player, Name::knight) {}

Knight::~Knight() {}

bool Knight::move_to(int x, int y, int xp, int yp) const
{
	return ((abs(xp - x) == 2 && abs(yp - y) == 1) ||
		(abs(xp - x) == 1 && abs(yp - y) == 2));
}

bool Knight::to_take(int x, int y, int xp, int yp) const
{
	return move_to(x, y, xp, yp);
}
