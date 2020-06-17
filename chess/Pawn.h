#pragma once

#include "IPiece.h"

class Pawn : public IPiece
{
public:
	Pawn();
	~Pawn();
	bool move_to(int x, int y);

private:

};
