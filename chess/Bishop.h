#pragma once

#include "IPiece.h"

class Bishop : public IPiece
{
public:
	Bishop(bool player = true);
	~Bishop();
	bool move_to(Coord& cd) const;
	bool to_take(Coord& cd) const;

private:

};
