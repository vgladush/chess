#pragma once

#include "Space.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

constexpr int SIZE = 333;
constexpr int WHITE = 0;
constexpr int BLACK = 333;
constexpr float GRID = 73.6;
constexpr int WIDTH = 1024;
constexpr int HEIGHT = 800;
constexpr float INDENT = 54;
constexpr float IND = 58.45;

using namespace sf;

class Gui_sfml
{
public:
	Gui_sfml();
	~Gui_sfml();

	bool draw_board(Space space[8][8], int &x, int &y, int &xp, int &yp, bool &help, std::string &err);

private:
	void draw_help(Space& space, int x, int y);
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
