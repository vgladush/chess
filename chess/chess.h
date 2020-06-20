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

	Gui_sfml gui;
	Space space[8][8];
	bool turn_w, help;
	Coord cd;
	Game gm;
	std::string error;
};
