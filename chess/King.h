#pragma once

#include "IPiece.h"

class King : public IPiece
{
public:
	King(bool player = true);
	~King();
	bool move_to(Coord& cd) const;
	bool to_take(Coord& cd) const;

private:

};
