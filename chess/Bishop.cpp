#include "Bishop.h"

Bishop::Bishop(bool player) : IPiece(player, Name::bishop) {}

Bishop::~Bishop() {}

bool Bishop::move_to(Coord& cd) const
{
	return (abs(cd.i - cd.x) == abs(cd.j - cd.y));
}

bool Bishop::to_take(Coord& cd) const
{
	return move_to(cd);
}
