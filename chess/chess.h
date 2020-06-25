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

	std::string check_way(); //free path to the goal
	void start(); //fill chessboard befor start the game
	bool set_movement(int plx, int ply, bool clear, bool mate = false);
	//check if there is another piece in the path and set help for moving
	
	bool castling(bool move, Coord& crd);
	bool check(bool move, Coord &ex); //check, 'ex' temporary coord for cheking
	bool can_beat(Coord& crd);
	bool check_king(int x = -1, int y = 0); //can something beat the king -1 - need to find the king
	bool checkmate();

	Gui_sfml gui; //engine
	Space space[8][8];
	bool turn_w, help; //white or black move, help display
	Coord cd, cr, castle; //'cd' for usual coordinates (currently and next position)
	//'cr' extra coord for en passant, x & y for white, i & j for black, value -1 is no pawn
	//'castle' for castling, x & y for white, i & j for black - left and right castling, 1 is true, 0 is false
	Game gm;
	std::string except; //exception (error or unusual situations)
};
