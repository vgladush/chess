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
	void menu();
	void move();
	void start();

	Gui_sfml gui;
	Space space[8][8];

};
