#pragma once

#include "IPiece.h"

class Rook : public IPiece
{
public:
	Rook(bool player = true);
	~Rook();
	bool move_to(Coord& cd) const;
	bool to_take(Coord& cd) const;

private:

};
