#include "Rook.h"

Rook::Rook(bool player) : IPiece(player, Name::rook) {}

Rook::~Rook() {}

bool Rook::move_to(int x, int y, int xp, int yp) const
{
	return (xp == x || yp == y);
}

bool Rook::to_take(int x, int y, int xp, int yp) const
{
	return (xp == x || yp == y);
}
