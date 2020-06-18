#pragma once

#include "Space.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define WIDTH 1024
#define HEIGHT 768

using namespace sf;

class Gui_sfml
{
public:
	Gui_sfml();
	~Gui_sfml();

	void draw_board(Space space[8][8], int &x, int &y, int &xp, int &yp);

private:
	RenderWindow window;
	Texture texture;
	Texture t_board;
	Sprite sp_board;
	Sprite sprite;
};
