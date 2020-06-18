#pragma once

#include "IPiece.h"

class King : public IPiece
{
public:
	King(bool player = true);
	~King();
	bool move_to(int x, int y, int xp, int yp) const;
	bool to_take(int x, int y, int xp, int yp) const;

private:

};
