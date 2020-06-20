#pragma once

#include "King.h"
#include "Knight.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"

enum class Move
{
	free, // can't move to space (not within reach)
	bit, // can bit
	empty, //can move
	stay // the piece that begins move
};

class Space
{
public:
	Space(IPiece* piece = nullptr);
	~Space();

	void setMove(Move mv);
	Move getMove();
	void setPiece(IPiece* cell);
	IPiece *getPiece();

private:

	IPiece* cell;
	Move move;

};
