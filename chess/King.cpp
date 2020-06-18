#include "King.h"

King::King(bool player) : IPiece(player) {}

King::~King() {}

bool King::move_to(int x, int y, int xp, int yp) const
{
	return (abs(xp - x) <= 1 && abs(yp - y) <= 1);
}

bool King::to_take(int x, int y, int xp, int yp) const
{
	return (abs(xp - x) <= 1 && abs(yp - y) <= 1);
}
