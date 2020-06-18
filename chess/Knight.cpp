#include "Knight.h"

Knight::Knight() {}

Knight::~Knight() {}

bool Knight::move_to(int x, int y) const
{
	return ((abs(getX() - x) == 2 && abs(getY() - y) == 1) ||
		(abs(getX() - x) == 1 && abs(getY() - y) == 2));
}

bool Knight::to_take(int x, int y) const
{
	return ((abs(getX() - x) == 2 && abs(getY() - y) == 1) ||
		(abs(getX() - x) == 1 && abs(getY() - y) == 2));
}
