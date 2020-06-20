#include "chess.h"
#include <iostream>
using namespace std;

Chess::Chess() : turn_w(true), help(true), clear(false), x(0), y(0), xp(0), yp(0) { }

Chess::~Chess() { }

void Chess::game()
{
	start();
	while (gui.draw_board(space, x, y, xp, yp, help, error))
	{
		if (space[x][y].getPiece()->getPlayer() != turn_w)
		{
			std::cout << "ne tvoy tern" << std::endl;
			continue;
		}
		if (help)
			check_movement();
		if (!check_way())
			std::cout << error << std::endl;
		else
			turn_w = !turn_w;
	}
}

bool Chess::check_way()
{
	error.clear();
	if (!space[x][y].getPiece()->move_to(x, y, xp, yp))
	{
		error = "tak dvigatsya nelzya";
		if (!space[xp][yp].getPiece() || space[x][y].getPiece()->getName() != Name::pawn
			|| !space[x][y].getPiece()->to_take(x, y, xp, yp))
			return false;
	}
	error = "pawn cant bit tak";
	if (space[xp][yp].getPiece() && space[x][y].getPiece()->getName() == Name::pawn
		&& space[x][y].getPiece()->move_to(x, y, xp, yp))
		return false;
	if (space[x][y].getPiece()->getName() != Name::knight && space[x][y].getPiece()->getName() != Name::king)
	{
		error = "na puti drugaya figura";
		if (x == xp)
		{
			int my = (y > yp ? -1 : 1);
			for (int i = y + my; i != yp; i += my)
			{
				if (space[x][i].getPiece())
					return false;
			}
		}
		else if (y == yp)
		{
			int mx = (x > xp ? -1 : 1);
			for (int i = x + mx; i != xp; i += mx)
			{
				if (space[i][y].getPiece())
					return false;
			}
		}
		else
		{
			int mx = (x < xp ? 1 : -1), my = (y < yp ? 1 : -1);
			for (int i = x + mx, j = y + my; i != xp; i += mx, j += my)
			{
				if (space[i][j].getPiece())
					return false;
			}
		}
	}
	error = "cant bit own piece";
	if (space[xp][yp].getPiece() && space[x][y].getPiece()->getPlayer() == space[xp][yp].getPiece()->getPlayer())
		return false;
	
	space[xp][yp].setPiece(space[x][y].getPiece());
	space[x][y].setPiece(nullptr);

	return true;
}

void Chess::menu()
{
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

void Chess::set_movement(int plx, int ply)
{
	//extra bit for pawn
	if (space[x][y].getPiece()->getName() == Name::pawn && 0 <= plx && plx < 8 && 8 > ply && ply >= 0
		&& space[x][y].getPiece()->to_take(x, y, plx, ply) && space[plx][ply].getPiece()
		&& space[plx][ply].getPiece()->getPlayer() != space[x][y].getPiece()->getPlayer())
		space[plx][ply].setMove((clear ? Move::free : Move::bit));

	//extra move for knight
	if (space[x][y].getPiece()->getName() == Name::knight)
	{
		if (plx == ply)
			ply += ply;
		else if (abs(plx) == abs(ply))
			plx += plx;
		else
		{
			plx += (plx == 0 ? -ply : plx);
			ply += plx + ply;
		}
	}

	for (int i = x + plx, j = y + ply; 0 <= i && i < 8 && 8 > j && j >= 0; i += plx, j += ply)
	{

		if (!space[x][y].getPiece()->move_to(x, y, i, j))
			return;
		if (!space[i][j].getPiece())
			space[i][j].setMove((clear ? Move::free : Move::empty));
		else
		{
			if (space[i][j].getPiece()->getPlayer() != space[x][y].getPiece()->getPlayer()
				&& space[x][y].getPiece()->getName() != Name::pawn)
				space[i][j].setMove((clear ? Move::free : Move::bit));
			return;
		}
	}
}

void Chess::check_movement()
{
	space[x][y].setMove((clear ? Move::free : Move::stay));
	//check move bottom
	set_movement(0, 1);
	//check move top
	set_movement(0, -1);
	//check move left
	set_movement(-1, 0);
	//check move right
	set_movement(1, 0);
	//check move diag bottom left
	set_movement(-1, 1);
	//check move diag bottom right 
	set_movement(1, 1);
	//check move diag top left
	set_movement(-1, -1);
	//check move diag top right 
	set_movement(1, -1);
}
