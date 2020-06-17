#include "King.h"

King::King() {}

King::~King() {}

bool King::move_to(int x, int y)
{
	return (abs(getX() - x) <= 1 && abs(getY() - y) <= 1);
}
