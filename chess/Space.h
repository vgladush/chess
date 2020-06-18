#pragma once

#include "King.h"
#include "Knight.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"

class Space
{
public:
	Space();
	~Space();
	template<IPiece*piece>
	bool chek_take(int x, int y) const;
	template<IPiece* piece>
	bool check_way(int x, int y) const;

private:
	IPiece* cell[8][8];

};
