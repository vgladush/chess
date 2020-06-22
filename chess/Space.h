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
	beat, // can beat
	empty, //can move
	stay, // the piece that begins move
	special //for castling or when a pawn turns into another piece
};

enum class Game
{
	start, //start or restart
	helper, // help, turn on or turn off
	hold, // start move 
	relesed, //end move
	clear, // clear helper
	castling, //to castle
	transf, //pawn transformation
	exit //game over
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

	IPiece* cell; //is there a piece on the checkerboard cell
	Move move; //cell status

};
