#include "Bishop.h"

Bishop::Bishop() {}

Bishop::~Bishop() {}

bool Bishop::move_to(int x, int y)
{
	return (abs(getX() - x) == abs(getY() - y));
}
