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
		if (gm == Game::start)
			start();
		else if (gm == Game::helper) //turn on, turn off helper
			help = !help;
		else if (gm == Game::transf) 
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
			except = "You can't move enemy pieces" + std::string(turn_w ? ". White" : ". Black") + ", make your move!";
		//after released, check player for correctness
		else if (gm == Game::relesed || gm == Game::transf)
		{
			except = (gm == Game::transf ? check_king() ? "check" : except : check_way());
			if (except.length() && except != "check" && except != "pawn")
				except += std::string(turn_w ? ". White" : ". Black") + ", make your move!";
			else
			{
				bool mate = checkmate();
				if (except == "check")
				{
					except = std::string(turn_w ? "White" : "Black") + ", your king is under attack. You check!";
					if (mate)
						except = (!turn_w ? "White won!" : "Black won!");
				}
				else if (mate)
					except = "Stalemate!\n   Draw!";
			}
		}
	}
}

std::string Chess::check_way()
{
	except.clear();
	bool cast = castling(true, cd);
	
	if (!cast)
	{
		bool pass = space[cd.x][cd.y].getPiece()->getName() == Name::pawn && ((cr.x == cd.i && cr.y == cd.j) || //if pawn, and 'en passant' or
			(cr.i == cd.i && cr.j == cd.j) || space[cd.i][cd.j].getPiece()) && space[cd.x][cd.y].getPiece()->to_take(cd); //is another piece and pawn can't beat
		
		//check whether the piece can walk like that
		if (!space[cd.x][cd.y].getPiece()->move_to(cd) && !cast && !pass)
			return (except.length() ? except : "This piece can't move like that");

		if (space[cd.i][cd.j].getPiece() && space[cd.x][cd.y].getPiece()->getName() == Name::pawn
			&& space[cd.x][cd.y].getPiece()->move_to(cd)) //pawn can't beat in a straight line
			return "Pawn can't beat like that";
		if (space[cd.x][cd.y].getPiece()->getName() != Name::knight && space[cd.x][cd.y].getPiece()->getName() != Name::king)
		{
			//check the way to the first oncoming piece or the end of the chessboard
			if (cd.x == cd.i) //horizontal
			{
				int my = (cd.y > cd.j ? -1 : 1);
				for (int i = cd.y + my; i != cd.j; i += my)
					if (space[cd.x][i].getPiece())
						return "You can't jump through pieces";

				//set coord for en passant
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
						return "You can't jump through pieces";
			}
			else //diagonal
			{
				//special conditions for a pawn

				int mx = (cd.x < cd.i ? 1 : -1), my = (cd.y < cd.j ? 1 : -1);
				for (int i = cd.x + mx, j = cd.y + my; i != cd.i; i += mx, j += my)
					if (space[i][j].getPiece())
						return "You can't jump through pieces";
			}
		}

		//checking if there was an attempt to beat own piece
		if (space[cd.i][cd.j].getPiece() && turn_w == space[cd.i][cd.j].getPiece()->getPlayer())
			return "You can't beat own piece";

		//pawn transformation
		if (space[cd.x][cd.y].getPiece()->getName() == Name::pawn && (cd.j == 0 || cd.j == 7))
			except = "pawn";

		if (check(true, cd))
			return "You can't move like that, you'll lose";
	}

	//if the check was successful, the piece has moved or beat another piece 

	turn_w = !turn_w; //change player

	if (check_king())
		except = "check";

	if (turn_w) //throw off en passant for opponent
		cr.i = cr.j = -1;
	else
		cr.x = cr.y = -1;

	if (castle.x && cd.y == 7 && (cd.x == 0 || cd.x == 4))
		castle.x = 0;
	if (castle.y && cd.y == 7 && (cd.x == 7 || cd.x == 4))
		castle.y = 0;
	if (castle.i && cd.y == 0 && (cd.x == 0 || cd.x == 4))
		castle.i = 0;
	if (castle.j && cd.y == 0 && (cd.x == 7 || cd.x == 4))
		castle.j = 0;

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

	except.clear();
	turn_w = true;
}

bool Chess::set_movement(int plx, int ply, bool clear, bool mate)
{
	Coord ex{ cd.x, cd.y, cd.x + plx, cd.y + ply }; //extra coordinates

	//extra beat for pawn
	if (space[cd.x][cd.y].getPiece()->getName() == Name::pawn && 0 <= ex.i && ex.i < 8
		&& ex.j < 8 && ex.j >= 0 && space[cd.x][cd.y].getPiece()->to_take(ex) &&	//if pawn can beat
		((space[ex.i][ex.j].getPiece() && turn_w != space[ex.i][ex.j].getPiece()->getPlayer()) //another piece
			|| (!turn_w && ex.i == cr.i && ex.j == cr.j) //en passant for white
			|| (turn_w && ex.i == cr.x && ex.j == cr.y))) //en passant for black
	{
		if (mate && !check(false, ex))
			return true;
		else if (!mate)
			space[ex.i][ex.j].setMove((clear || check(false, ex) ? Move::free : (ex.j == 0 || ex.j == 7 ? Move::special : Move::beat)));
	}
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

	//check can move or beat
	for ( ; 0 <= ex.i && ex.i < 8 && 8 > ex.j && ex.j >= 0; ex.i += plx, ex.j += ply) 
	{
		if (!mate && castling(false, ex))
			space[ex.i][ex.j].setMove((clear || check(false, ex) ? Move::free : Move::beat));
		if (!space[cd.x][cd.y].getPiece()->move_to(ex)) //can't move
			return false;
		if (!space[ex.i][ex.j].getPiece()) //no piece
		{
			if (mate && !check(false, ex))
				return true;
			else if (!mate)
				space[ex.i][ex.j].setMove((clear || check(false, ex) ? Move::free : Move::empty)); //free way
			if (!mate && space[cd.x][cd.y].getPiece()->getName() == Name::pawn && (ex.j == 0 || ex.j == 7))
				space[ex.i][ex.j].setMove(Move::special); //en passant
		}
		else
		{
			if (space[ex.i][ex.j].getPiece()->getPlayer() != turn_w &&
				space[cd.x][cd.y].getPiece()->getName() != Name::pawn)
			{
				if (mate && !check(false, ex))
					return true;
				else if (!mate)
					space[ex.i][ex.j].setMove((clear || check(false, ex) ? Move::free : Move::beat));
			}
			return false;
		}
	}
	return false;
}

bool Chess::castling(bool move, Coord& crd)
{
	if (space[crd.x][crd.y].getPiece()->getName() != Name::king)
		return false;
	int can = 0; // -1 left, 1 right, 0 false
	if (crd.i == 2 && ((crd.j == 7 && castle.x && turn_w) || (crd.j == 0 && castle.i && !turn_w)) && //long castling
		!space[crd.x - 1][crd.y].getPiece() && !space[crd.x - 2][crd.y].getPiece() && !space[crd.x - 3][crd.y].getPiece())
		can = -1;
	if (crd.i == 6 && ((crd.j == 7 && castle.y && turn_w) || (crd.j == 0 && castle.j && !turn_w))
		&& !space[crd.x + 1][crd.y].getPiece() && !space[crd.x + 2][crd.y].getPiece()) //short castling
		can = 1;
	if (can && (check_king(crd.x, crd.y) || check_king(crd.x + can, crd.y) || check_king(crd.i, crd.y)))
	{
		if (move)
			except = "You can't castle, there is a threat";
		return false;
	}
	if (can && move)
	{
		space[crd.x + can][crd.y].setPiece(space[(can == 1 ? 7 : 0)][crd.y].getPiece());
		space[(can == 1 ? 7 : 0)][crd.y].setPiece(nullptr);
		space[crd.i][crd.y].setPiece(space[crd.x][crd.y].getPiece());
		space[crd.x][crd.y].setPiece(nullptr);
	}

	return can;
}

// checking check color, need to move, coordinates pieces and extra for castling or en passant
bool Chess::check(bool move, Coord& ex)
{
	bool ck = false;
	IPiece* tmp;

	bool pass = space[ex.x][ex.y].getPiece()->getName() == Name::pawn && space[ex.x][ex.y].getPiece()->to_take(ex); //if pawn beat
	if (pass && cr.x == ex.i && cr.y == ex.j) //if was en passant black
	{
		tmp = space[ex.i][ex.j + 1].getPiece();
		space[ex.i][ex.j + 1].setPiece(nullptr);
	}
	else if (pass && cr.i == ex.i && cr.j == ex.j) //if was en passant white
	{
		tmp = space[ex.i][ex.j - 1].getPiece();
		space[ex.i][ex.j - 1].setPiece(nullptr);
	}
	else
		tmp = space[ex.i][ex.j].getPiece();

	space[ex.i][ex.j].setPiece(space[ex.x][ex.y].getPiece());
	space[ex.x][ex.y].setPiece(nullptr);

	ck = check_king();

	if (!move || ck)
	{
		space[ex.x][ex.y].setPiece(space[ex.i][ex.j].getPiece());
		space[ex.i][ex.j].setPiece(nullptr);
		if (pass && cr.x == ex.i && cr.y == ex.j) //en passant black
			space[ex.i][ex.j + 1].setPiece(tmp);
		else if (pass && cr.i == ex.i && cr.j == ex.j) //en passant white
			space[ex.i][ex.j - 1].setPiece(tmp);
		else
			space[ex.i][ex.j].setPiece(tmp);
	}
	else
		delete tmp;

	return ck;
}

bool Chess::can_beat(Coord& crd) //can a piece beat a king
{
	if (!crd.x && !crd.y)
		return false;
	Coord kng = { crd.x + crd.i,  crd.y + crd.j, crd.i, crd.j };
	for (; kng.x < 8 && kng.y < 8 && kng.x > -1 && kng.y > -1; kng.x += crd.x, kng.y += crd.y)
	{
		if (space[kng.x][kng.y].getPiece())
		{
			if (space[kng.x][kng.y].getPiece()->getPlayer() != turn_w && space[kng.x][kng.y].getPiece()->to_take(kng))
				return true;
			break;
		}
	}

	//extra chek for knight
	if (crd.x == crd.y)
		kng = { crd.x + crd.i, 2 * crd.y + crd.j, crd.i, crd.j };
	else if (abs(crd.x) == abs(crd.y))
		kng = { 2 * crd.x + crd.i,  crd.y + crd.j, crd.i, crd.j };
	else
		kng = { crd.x + crd.i + (crd.x == 0 ? -crd.y : crd.x),  2 * crd.y + crd.j + crd.x, crd.i, crd.j };
	if (kng.x < 8 && kng.y < 8 && kng.x > -1 && kng.y > -1 && space[kng.x][kng.y].getPiece() &&
		space[kng.x][kng.y].getPiece()->getPlayer() != turn_w && space[kng.x][kng.y].getPiece()->to_take(kng))
		return true;
	return false;
}

bool Chess::check_king(int x, int y)
{
	Coord kng = { 8, 8, x, y };

	//find king
	if (x == -1)
	{
		for (kng.i = 0; kng.i < kng.x; ++kng.i)
			for (kng.j = 0; kng.j < kng.y; ++kng.j)
				if (space[kng.i][kng.j].getPiece() && space[kng.i][kng.j].getPiece()->getName()
					== Name::king && space[kng.i][kng.j].getPiece()->getPlayer() == turn_w)
					kng.x = kng.y = 0;
		--kng.i;
		--kng.j;
	}

	//find enemy pieces and see if they can beat the king, horizontal vertical etc.
	for (kng.x = -1; kng.x < 2; kng.x++)
		for (kng.y = -1; kng.y < 2; kng.y++)
			if (can_beat(kng))
				return true;

	return false;
}

bool Chess::checkmate()
{
	for (cd.x = 0; cd.x < 8; cd.x++)
		for (cd.y = 0; cd.y < 8; cd.y++)
			if (space[cd.x][cd.y].getPiece() && space[cd.x][cd.y].getPiece()->getPlayer() == turn_w)
				for (int x = -1; x < 2; x++)
					for (int y = -1; y < 2; y++)
						if (!(!x && !y) && set_movement(x, y, true, true))
							return false;
	return true;
}
