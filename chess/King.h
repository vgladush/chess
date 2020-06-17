#pragma once

#include "IPiece.h"

class King : public IPiece
{
public:
	King();
	~King();
	bool move_to(int x, int y) const;

private:

};
