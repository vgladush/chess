#include "Rook.h"

Rook::Rook() {}

Rook::~Rook() {}

bool Rook::move_to(int x, int y) const
{
	return (getX() == x || getY() == y);
}

bool Rook::to_take(int x, int y) const
{
	return (getX() == x || getY() == y);
}
