#pragma once

#include "Space.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

constexpr int SIZE = 333;
constexpr int WHITE = 0;
constexpr int BLACK = 333;
constexpr float GRID = 74;
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

	Game draw_board(Space space[8][8], Coord& cd, std::string &err); //main method

private:
	void draw_help(Space& space, int x, int y); //if help turned on
	void draw_space(IPiece* piece, Coord& crd); //chessboard display

	RenderWindow window;
	Texture texture, t_board, t_help; //texture for space and other, separate texture for background and helper
	Sprite sprite, sp_board, sp_help; //sprite for space and other, separate sprite for background and helper
	Vector2i v2i; //for pulling out coordinates
	bool hold, help; //pressed left mouse key, help turn on
};
