#pragma once

#include "IPiece.h"

class Pawn : public IPiece
{
public:
	Pawn(bool player = true);
	~Pawn();
	bool move_to(Coord& cd) const;
	bool to_take(Coord& cd) const;

private:

};
