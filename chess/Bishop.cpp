#include "Bishop.h"

Bishop::Bishop() {}

Bishop::~Bishop() {}

bool Bishop::move_to(int x, int y) const
{
	return (abs(getX() - x) == abs(getY() - y));
}

bool Bishop::to_take(int x, int y) const
{
	return (abs(getX() - x) == abs(getY() - y));
}
