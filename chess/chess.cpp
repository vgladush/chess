#include "chess.h"

Chess::Chess() : turn_w(true), help(false)
{
	cd = { 0, 0, 0, 0};
	castle = { 1, 1, 1, 1 };
	passant = { -1, -1, -1, -1 };
}

Chess::~Chess() { }

void Chess::game()
{
	start();
	while ((gm = gui.draw_board(space, cd, error)) != Game::exit) // while open window
	{
		if (gm == Game::helper)
		{
			help = !help;
			continue;
		}
		if (help && space[cd.x][cd.y].getPiece()->getPlayer() == turn_w) //if help is on
		{
			if (gm == Game::hold)
				check_movement(false); //after hold, calculate the options for moves
			else
				check_movement(true); //after released, clear the options for moves
		}
		//if not player turn
		if (gm == Game::relesed && space[cd.x][cd.y].getPiece()->getPlayer() != turn_w)
			error = "now the move is " + std::string(turn_w ? "white" : "black");
		//after released, check player for correctness
		else if (gm == Game::relesed && check_way())
			turn_w = !turn_w; //change player
	}
}

bool Chess::check_way()
{
	error.clear();
	if (!space[cd.x][cd.y].getPiece()->move_to(cd))
	{
		//check whether the piece can walk like that
		error = "this piece can't move like that";
		if (space[cd.x][cd.y].getPiece()->getName() != Name::pawn || (!(passant.x == cd.i //if not a pawn
			&& passant.y == cd.j) && !(passant.i == cd.i && passant.j == cd.j) && //or pawn, and 'en passant' or
			!space[cd.i][cd.j].getPiece()) || !space[cd.x][cd.y].getPiece()->to_take(cd)) //is another piece and pawn can beat
			return false;
	}
	error = "pawn can't beat like that";
	if (space[cd.i][cd.j].getPiece() && space[cd.x][cd.y].getPiece()->getName() == Name::pawn
		&& space[cd.x][cd.y].getPiece()->move_to(cd)) //pawn can't beat in a straight line
		return false;
	if (space[cd.x][cd.y].getPiece()->getName() != Name::knight && space[cd.x][cd.y].getPiece()->getName() != Name::king)
	{
		//checking the path to the first oncoming piece or the end of the chessboard
		error = "there is a piece or pieces in the way";
		if (cd.x == cd.i) //horizontal
		{
			int my = (cd.y > cd.j ? -1 : 1);
			for (int i = cd.y + my; i != cd.j; i += my)
				if (space[cd.x][i].getPiece())
					return false;
			
			//set coord en passant
			if (space[cd.x][cd.y].getPiece()->getName() == Name::pawn && abs(cd.j - cd.y) == 2)
			{
				passant.i = passant.x = cd.x;
				passant.y = passant.j = cd.j - my;
			}
		}
		else if (cd.y == cd.j) //vertical
		{
			int mx = (cd.x > cd.i ? -1 : 1);
			for (int i = cd.x + mx; i != cd.i; i += mx)
				if (space[i][cd.y].getPiece())
					return false;
		}
		else //diagonal
		{
			//special conditions for a pawn

			int mx = (cd.x < cd.i ? 1 : -1), my = (cd.y < cd.j ? 1 : -1);
			for (int i = cd.x + mx, j = cd.y + my; i != cd.i; i += mx, j += my)
				if (space[i][j].getPiece())
					return false;
		}
	}

	error = "you can't beat own piece";
	//checking if there was an attempt to beat own pawn
	if (space[cd.i][cd.j].getPiece() && turn_w == space[cd.i][cd.j].getPiece()->getPlayer())
		return false;
	
	//if the check was successful, the piece has moved or beat another piece 
	error.clear();
	space[cd.i][cd.j].setPiece(space[cd.x][cd.y].getPiece());
	space[cd.x][cd.y].setPiece(nullptr);

	//if was en passant
	if (passant.x == cd.i && passant.y == cd.j)
		space[cd.i][cd.j - 1].setPiece(nullptr);
	else if (passant.i == cd.i && passant.j == cd.j)
		space[cd.i][cd.j + 1].setPiece(nullptr);

	if (turn_w) //throw off en passant for opponent
		passant.i = passant.j = -1;
	else
		passant.x = passant.y = -1;

	return true;
}

void Chess::start()
{
	//fill the chessboard with pieces
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
void Chess::set_movement(int plx, int ply, bool clear)
{
	Coord ex{ cd.x, cd.y, cd.x + plx, cd.y + ply }; //extra coordinates

	//extra beat for pawn
	if (space[cd.x][cd.y].getPiece()->getName() == Name::pawn && 0 <= ex.i && ex.i < 8  
		&& ex.j < 8 && ex.j >= 0 && space[cd.x][cd.y].getPiece()->to_take(ex) &&
		((space[ex.i][ex.j].getPiece() && turn_w != space[ex.i][ex.j].getPiece()->getPlayer()) //if pawn can beat another piece
		|| (turn_w && ex.i == passant.i && ex.j == passant.j) //en passant for white
		|| (!turn_w && ex.i == passant.x && ex.j == passant.y))) //en passant for black
		space[ex.i][ex.j].setMove((clear ? Move::free : Move::beat));
	//extra move for knight
	if (space[cd.x][cd.y].getPiece()->getName() == Name::knight)
	{
		if (plx == ply)
			ex.j += ply;
		else if (abs(plx) == abs(ply))
			ex.i += plx;
		else
		{
			ex.i += (plx == 0 ? -ply : plx);
			ex.j += plx + ply;
		}
	}

	for ( ; 0 <= ex.i && ex.i < 8 && 8 > ex.j && ex.j >= 0; ex.i += plx, ex.j += ply) //check can move or beat
	{
		if (!space[cd.x][cd.y].getPiece()->move_to(ex))
			return;
		if (!space[ex.i][ex.j].getPiece())
			space[ex.i][ex.j].setMove((clear ? Move::free : Move::empty));
		else
		{
			if (space[ex.i][ex.j].getPiece()->getPlayer() != turn_w
				&& space[cd.x][cd.y].getPiece()->getName() != Name::pawn)
				space[ex.i][ex.j].setMove((clear ? Move::free : Move::beat));
			return;
		}
	}
}

void Chess::check_movement(bool clear)
{
	space[cd.x][cd.y].setMove((clear ? Move::free : Move::stay));
	//check move bottom
	set_movement(0, 1, clear);
	//check move top
	set_movement(0, -1, clear);
	//check move left
	set_movement(-1, 0, clear);
	//check move right
	set_movement(1, 0, clear);
	//check move diag bottom left
	set_movement(-1, 1, clear);
	//check move diag bottom right 
	set_movement(1, 1, clear);
	//check move diag top left
	set_movement(-1, -1, clear);
	//check move diag top right 
	set_movement(1, -1, clear);
}
