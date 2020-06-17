#pragma once

#include "IPiece.h"

class Bishop : public IPiece
{
public:
	Bishop();
	~Bishop();
	bool move_to(int x, int y) const;

private:

};
