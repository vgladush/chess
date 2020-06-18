#include "chess.h"

Chess::Chess()
{
}

Chess::~Chess()
{
}

void Chess::game()
{
	start();
	move();
}

void Chess::menu()
{
}

void Chess::move()
{
	int x, y, xp, yp;
	gui.draw_board(space, x, y, xp, yp);
}

void Chess::start()
{
	space[0][0].setPiece(new Rook(false));
	space[1][0].setPiece(new Knight(false));
	space[2][0].setPiece(new Bishop(false));
	space[3][0].setPiece(new Queen(false));
	space[4][0].setPiece(new King(false));
	space[5][0].setPiece(new Bishop(false));
	space[6][0].setPiece(new Knight(false));
	space[7][0].setPiece(new Rook(false));
	space[0][1].setPiece(new Pawn(false));
	space[1][1].setPiece(new Pawn(false));
	space[2][1].setPiece(new Pawn(false));
	space[3][1].setPiece(new Pawn(false));
	space[4][1].setPiece(new Pawn(false));
	space[5][1].setPiece(new Pawn(false));
	space[6][1].setPiece(new Pawn(false));
	space[7][1].setPiece(new Pawn(false));

	space[0][6].setPiece(new Pawn);
	space[1][6].setPiece(new Pawn);
	space[2][6].setPiece(new Pawn);
	space[3][6].setPiece(new Pawn);
	space[4][6].setPiece(new Pawn);
	space[5][6].setPiece(new Pawn);
	space[6][6].setPiece(new Pawn);
	space[7][6].setPiece(new Pawn);
	space[0][7].setPiece(new Rook);
	space[1][7].setPiece(new Knight);
	space[2][7].setPiece(new Bishop);
	space[3][7].setPiece(new Queen);
	space[4][7].setPiece(new King);
	space[5][7].setPiece(new Bishop);
	space[6][7].setPiece(new Knight);
	space[7][7].setPiece(new Rook);

}
