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
	void menu();
	void start();
	void set_movement(int plx, int ply);
	void check_movement();

	Gui_sfml gui;
	Space space[8][8];
	bool turn_w, help, clear;
	int x, y, xp, yp;
	std::string error;
};
