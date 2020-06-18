#pragma once

#include "IPiece.h"

class King : public IPiece
{
public:
	King();
	~King();
	bool move_to(int x, int y) const;
	bool to_take(int x, int y) const;

private:

};
