#pragma once

#include "IPiece.h"

class Bishop : public IPiece
{
public:
	Bishop(bool player = true);
	~Bishop();
	bool move_to(int x, int y, int xp, int yp) const;
	bool to_take(int x, int y, int xp, int yp) const;

private:

};
