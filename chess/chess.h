#pragma once

#include "Space.h"
#include "gui_sfml.h"

class Chess
{
public:
	Chess();
	~Chess();
	void game();

private:

	bool check_way(); //free path to the goal
	void start(); //fill chessboard befor start the game
	void set_movement(int plx, int ply, bool clear); //set help for moving
	void check_movement(bool clear); //check if there is another piece in the path

	Gui_sfml gui; //engine
	Space space[8][8];
	bool turn_w, help; //white or black move, help display
	Coord cd, castle, passant;
	//'cd' for usual coordinates (currently and next position)
	//'castle' for ñastling, x & y for white, i & j for black - left and right ñastling, 1 is true, 0 is false
	// 'paasant' extra coord for en passant, x & y for white, i & j for black, value -1 is no pawn
	Game gm;
	std::string except; //exception (error or unusual situations)
};
