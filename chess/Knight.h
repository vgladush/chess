#pragma once

#include "IPiece.h"

class Knight : public IPiece
{
public:
	Knight(bool player = true);
	~Knight();
	bool move_to(Coord& cd) const;
	bool to_take(Coord& cd) const;

private:

};
