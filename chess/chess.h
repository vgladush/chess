#pragma once

#include "Space.h"
#include "gui_sfml.h"
#include <SFML\Graphics\Color.hpp>

class Chess
{
public:
	Chess();
	~Chess();
	void game();

private:

	bool check_way(); //free path to the goal
	void start(); //fill chessboard befor start the game
	void set_movement(int plx, int ply, bool clear);
	//check if there is another piece in the path and set help for moving
	
	bool check(bool move);
	bool checkmate();
	bool check_king();

	Gui_sfml gui; //engine
	Space space[8][8];
	bool turn_w, help; //white or black move, help display
	Coord cd, cr, castle;
	//'cd' for usual coordinates (currently and next position)
	//'cr' for 'paasant' extra coord for en passant, x & y for white, i & j for black, value -1 is no pawn
	//'castle 'for 'castle' for castling, x & y for white, i & j for black - left and right castling, 1 is true, 0 is false
	Game gm;
	std::string except; //exception (error or unusual situations)
};
