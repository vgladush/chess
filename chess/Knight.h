#pragma once

#include "IPiece.h"

class Knight : public IPiece
{
public:
	Knight(bool player = true);
	~Knight();
	bool move_to(int x, int y, int xp, int yp) const;
	bool to_take(int x, int y, int xp, int yp) const;

private:

};
