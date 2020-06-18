#pragma once

#include "IPiece.h"

class Queen : public IPiece
{
public:
	Queen(bool player = true);
	~Queen();
	bool move_to(int x, int y, int xp, int yp) const;
	bool to_take(int x, int y, int xp, int yp) const;

private:

};

