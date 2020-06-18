#pragma once

#include "IPiece.h"

class Rook : public IPiece
{
public:
	Rook();
	~Rook();
	bool move_to(int x, int y) const;
	bool to_take(int x, int y) const;

private:

};
