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
	Space(IPiece* piece = nullptr);
	~Space();

	bool chek_take(int x, int y, int xp, int yp) const; //
	bool check_way(int x, int y, int xp, int yp)const; //free path to the goal
	void setPiece(IPiece* cell);
	IPiece *getPiece();

private:
	void clear();

	IPiece* cell;

};
