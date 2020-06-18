#pragma once

#include "IPiece.h"

class Rook : public IPiece
{
public:
	Rook(bool player = true);
	~Rook();
	bool move_to(int x, int y, int xp, int yp) const;
	bool to_take(int x, int y, int xp, int yp) const;

private:

};
