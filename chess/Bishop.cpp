#include "Bishop.h"

Bishop::Bishop(bool player) : IPiece(player, Name::bishop) {}

Bishop::~Bishop() {}

bool Bishop::move_to(int x, int y, int xp, int yp) const
{
	return (abs(xp - x) == abs(yp - y));
}

bool Bishop::to_take(int x, int y, int xp, int yp) const
{
	return move_to(x, y, xp, yp);
}
