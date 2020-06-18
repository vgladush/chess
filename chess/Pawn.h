#pragma once

#include "IPiece.h"

class Pawn : public IPiece
{
public:
	Pawn(bool player = true);
	~Pawn();
	bool move_to(int x, int y, int xp, int yp) const;
	bool to_take(int x, int y, int xp, int yp) const;

private:

};
