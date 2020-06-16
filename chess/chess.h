#pragma once

#include "gui_sfml.h"
#include <list>

#define WIDTH 1000
#define HEIGHT 830

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
	std::list<int8_t[8][8]> turn;
	bool forward;


};
