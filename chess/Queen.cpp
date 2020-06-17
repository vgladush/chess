#include "Queen.h"

Queen::Queen() {}

Queen::~Queen() {}

bool Queen::move_to(int x, int y)
{
	return (abs(getX() - x) == abs(getY() - y)
		|| getX() == x || getY() == y);
}
