#pragma once

#include "IPiece.h"

class Queen : public IPiece
{
public:
	Queen(bool player = true);
	~Queen();
	bool move_to(Coord& cd) const;
	bool to_take(Coord& cd) const;

private:

};

