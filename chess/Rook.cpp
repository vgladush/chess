#include "Rook.h"

Rook::Rook(bool player) : IPiece(player, Name::rook) {}

Rook::~Rook() {}

bool Rook::move_to(Coord& cd) const
{
	return (cd.i == cd.x || cd.j == cd.y);
}

bool Rook::to_take(Coord& cd) const
{
	return move_to(cd);
}
