#pragma once

#include "gui_sfml.h"
#include "King.h"

class Chess
{
public:
	Chess();
	~Chess();
	void game();

private:
	void menu();
	void move();
	void start();

	Gui_sfml gui;
	Space space[8][8];

};
