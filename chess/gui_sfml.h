#pragma once

#include "Space.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

constexpr int SIZE = 333;
constexpr int WHITE = 0;
constexpr int BLACK = 333;
constexpr int GRID = 74;
constexpr int WIDTH = 1024;
constexpr int HEIGHT = 768;
constexpr int TOP = 54;
constexpr int LEFT = 201;

using namespace sf;

class Gui_sfml
{
public:
	Gui_sfml();
	~Gui_sfml();

	void draw_board(Space space[8][8], int &x, int &y, int &xp, int &yp);

private:
	void draw_space(IPiece* piece, int x, int y);

	RenderWindow window;
	Texture texture;
	Texture t_board;
	Sprite sp_board;
	Sprite sprite;
	Vector2i v2i;
	bool hold;
	int mvx, mvy;
};
