#pragma once

#include "IPiece.h"

class Knight : public IPiece
{
public:
	Knight();
	~Knight();
	bool move_to(int x, int y) const;

private:

};

