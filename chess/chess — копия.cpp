#include "chess.h"

Chess::Chess() : turn_w(true), help(false), gm(Game::start)
{
	cd = { 0, 0, 0, 0};
	castle = { 1, 1, 1, 1 };
	cr = { -1, -1, -1, -1 };
}

Chess::~Chess() { }

void Chess::game()
{
	start();
	while ((gm = gui.draw_board(space, cd, except)) != Game::exit) // while open window
	{
		if (gm == Game::helper) //turn on, turn off helper
			help = !help;
		else if (gm == Game::transf && cd.x > 1 && cd.x < 6) 
		{
			//pawn transformation, replacing a pawn with a selected piece
			delete space[cd.i][cd.j].getPiece();
			if (cd.x == 2)
				space[cd.i][cd.j].setPiece(new Queen(!turn_w));
			else if (cd.x == 3)
				space[cd.i][cd.j].setPiece(new Bishop(!turn_w));
			else if (cd.x == 4)
				space[cd.i][cd.j].setPiece(new Knight(!turn_w));
			else
				space[cd.i][cd.j].setPiece(new Rook(!turn_w));
			except = "spec";

			//clear helper
			for (int i = cd.i - 2; i < cd.i + 3; i++)
				space[i][cd.j].setMove(Move::free);
		}
		else if (help && space[cd.x][cd.y].getPiece()->getPlayer() == turn_w) //if help is on
		{
			space[cd.x][cd.y].setMove((gm != Game::hold ? Move::free : Move::stay));
			//check move bottom, top, right, left, and all diagonal
			for (int i = -1; i < 2; i++)
				for (int j = -1; j < 2; j++)
					set_movement(i, j, (gm != Game::hold));
			//false - after hold, calculate the options for moves
			//true - after released, clear the options for moves
		}
		//if the turn of the wrong player
		if (gm == Game::relesed && space[cd.x][cd.y].getPiece()->getPlayer() != turn_w)
			except = "now the move is " + std::string(turn_w ? "white" : "black");
		//after released, check player for correctness
		else if (gm == Game::relesed)
			except = check_way();
		if (gm == Game::start)
			start();
	}
}

std::string Chess::check_way()
{
	except.clear();
	if (!space[cd.x][cd.y].getPiece()->move_to(cd))
	{
		//check whether the piece can walk like that
		if (space[cd.x][cd.y].getPiece()->getName() != Name::pawn || (!(cr.x == cd.i //if not a pawn
			&& cr.y == cd.j) && !(cr.i == cd.i && cr.j == cd.j) && //or pawn, and 'en passant' or
			!space[cd.i][cd.j].getPiece()) || !space[cd.x][cd.y].getPiece()->to_take(cd)) //is another piece and pawn can't beat
			return "this piece can't move like that";
	}
	if (space[cd.i][cd.j].getPiece() && space[cd.x][cd.y].getPiece()->getName() == Name::pawn
		&& space[cd.x][cd.y].getPiece()->move_to(cd)) //pawn can't beat in a straight line
		return "pawn can't beat like that";
	if (space[cd.x][cd.y].getPiece()->getName() != Name::knight && space[cd.x][cd.y].getPiece()->getName() != Name::king)
	{
		//checking the path to the first oncoming piece or the end of the chessboard
		if (cd.x == cd.i) //horizontal
		{
			int my = (cd.y > cd.j ? -1 : 1);
			for (int i = cd.y + my; i != cd.j; i += my)
				if (space[cd.x][i].getPiece())
					return "there is a piece or pieces in the way";
			
			//set coord en passant
			if (space[cd.x][cd.y].getPiece()->getName() == Name::pawn && abs(cd.j - cd.y) == 2)
			{
				cr.i = cr.x = cd.x;
				cr.y = cr.j = cd.j - my;
			}
		}
		else if (cd.y == cd.j) //vertical
		{
			int mx = (cd.x > cd.i ? -1 : 1);
			for (int i = cd.x + mx; i != cd.i; i += mx)
				if (space[i][cd.y].getPiece())
					return "there is a piece or pieces in the way";
		}
		else //diagonal
		{
			//special conditions for a pawn

			int mx = (cd.x < cd.i ? 1 : -1), my = (cd.y < cd.j ? 1 : -1);
			for (int i = cd.x + mx, j = cd.y + my; i != cd.i; i += mx, j += my)
				if (space[i][j].getPiece())
					return "there is a piece or pieces in the way";
		}
	}

	//checking if there was an attempt to beat own pawn
	if (space[cd.i][cd.j].getPiece() && turn_w == space[cd.i][cd.j].getPiece()->getPlayer())
		return "you can't beat own piece";
	
	//if the check was successful, the piece has moved or beat another piece 
	if (space[cd.x][cd.y].getPiece()->getName() == Name::pawn && (cd.j == 0 || cd.j == 7))
		except = "pawn";
	delete space[cd.i][cd.j].getPiece();
	space[cd.i][cd.j].setPiece(space[cd.x][cd.y].getPiece());
	//delete space[cd.x][cd.y].getPiece();
	space[cd.x][cd.y].setPiece(nullptr);

	//if was en passant
	if (cr.x == cd.i && cr.y == cd.j)
		space[cd.i][cd.j - 1].setPiece(nullptr);
	else if (cr.i == cd.i && cr.j == cd.j)
		space[cd.i][cd.j + 1].setPiece(nullptr);

	if (turn_w) //throw off en passant for opponent
		cr.i = cr.j = -1;
	else
		cr.x = cr.y = -1;

	//throw off castling
	if (castle.x && cd.y == 7 && (cd.x == 0 || cd.x == 4))
		castle.x = 0;
	if (castle.y && cd.y == 7 && (cd.x == 7 || cd.x == 4))
		castle.y = 0;
	if (castle.i && cd.y == 0 && (cd.x == 0 || cd.x == 4))
		castle.i = 0;
	if (castle.j && cd.y == 0 && (cd.x == 7 || cd.x == 4))
		castle.j = 0;

	turn_w = !turn_w; //change player
	return except;
}

void Chess::start()
{
	//clear the chessboard
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			delete space[i][j].getPiece();
			space[i][j].setPiece(nullptr);
		}
	}
	
	//fill the chessboard with pieces
	space[0][0].setPiece(new Rook(false));
	space[1][0].setPiece(new Knight(false));
	space[2][0].setPiece(new Bishop(false));
	space[3][0].setPiece(new Queen(false));
	space[4][0].setPiece(new King(false));
	space[5][0].setPiece(new Bishop(false));
	space[6][0].setPiece(new Knight(false));
	space[7][0].setPiece(new Rook(false));
	for (int i = 0; i < 8; ++i)
		space[i][1].setPiece(new Pawn(false));

	for (int i = 0; i < 8; ++i)
		space[i][6].setPiece(new Pawn);
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
		&& ex.j < 8 && ex.j >= 0 && space[cd.x][cd.y].getPiece()->to_take(ex) &&	//if pawn can beat
		((space[ex.i][ex.j].getPiece() && turn_w != space[ex.i][ex.j].getPiece()->getPlayer()) //another piece
		|| (turn_w && ex.i == cr.i && ex.j == cr.j) //en passant for white
		|| (!turn_w && ex.i == cr.x && ex.j == cr.y))) //en passant for black
		space[ex.i][ex.j].setMove((clear || check(false, ex) ? Move::free : (ex.j == 0 || ex.j == 7 ? Move::special : Move::beat)));
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
		if (!space[cd.x][cd.y].getPiece()->move_to(ex)) //can't move
			return;
		if (!space[ex.i][ex.j].getPiece()) //no piece
		{
			space[ex.i][ex.j].setMove((clear || check(false, ex) ? Move::free : Move::empty)); //free way
			if (space[cd.x][cd.y].getPiece()->getName() == Name::pawn && (ex.j == 0 || ex.j == 7))
				space[ex.i][ex.j].setMove(Move::special); //en passant
		}
		else
		{
			if (space[ex.i][ex.j].getPiece()->getPlayer() != turn_w &&
				space[cd.x][cd.y].getPiece()->getName() != Name::pawn)
				space[ex.i][ex.j].setMove((clear || check(false, ex) ? Move::free : Move::beat));
			return;
		}
	}
}

// checking check color, need to move, coordinates pieces and extra for castling or en passant
bool Chess::check(bool move, Coord& ex)
{
	bool check = false;
	IPiece* tmp1 = space[ex.i][ex.j].getPiece(); //taked piece
	space[ex.i][ex.j].setPiece(space[ex.x][ex.y].getPiece());
	space[ex.x][ex.y].setPiece(nullptr);
	
	IPiece* tmp2 = nullptr;//castling or pawn transform
	if (cr.x != -1)
	{
		tmp2 = space[cr.x][cr.y].getPiece();
		if (cr.i != -1)
		{
			space[cr.x][cr.y].setPiece(space[cr.i][cr.j].getPiece());
			space[cr.i][cr.j].setPiece(tmp2);
		}
		else
			space[cr.x][cr.y].setPiece(nullptr);
	}

	check = check_king();

	if (!move)
	{
		space[ex.x][ex.y].setPiece(space[ex.i][ex.j].getPiece());
		space[ex.i][ex.j].setPiece(tmp1);
		if (cr.x != -1)
		{
			if ((cr.i != -1))
			{
				space[ex.i][ex.j].setPiece(space[ex.x][ex.y].getPiece());
			}
			space[cr.x][cr.y].setPiece(tmp2);
		}
	}

	return check;
}

bool Chess::check_king()
{
	Coord kng = { 8, 8, 0, 0 };
	//find king
	for ( ; kng.i < kng.x; ++kng.i)
		for (kng.j = 0; kng.j < kng.y; ++kng.j)
			if (space[kng.i][kng.j].getPiece() && space[kng.i][kng.j].getPiece()->getName() ==
				Name::king && space[kng.i][kng.j].getPiece()->getPlayer() == turn_w)
				kng.x = kng.y = 0;
	--kng.i;
	--kng.j;

	//find enemy pieces and see if they can beat the king
	for ( ; kng.x < 8; kng.x++)
	{
		for (kng.y = 0; kng.y < 8; kng.y++)
		{
			if (space[kng.x][kng.y].getPiece() && space[kng.x][kng.y].getPiece()->getPlayer()
				!= turn_w && space[kng.x][kng.y].getPiece()->to_take(kng))
				return true;
		}
	}
	return false;
}

bool Chess::checkmate()
{
	//for (int i = 0; i < length; i++)
	{

	}

	return false;
}
