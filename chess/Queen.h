#pragma once

#include "IPiece.h"

class Queen : public IPiece
{
public:
	Queen();
	~Queen();
	bool move_to(int x, int y) const;

private:

};
