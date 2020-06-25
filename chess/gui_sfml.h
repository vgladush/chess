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

	Game draw_board(Space space[8][8], Coord& cd, std::string& stat); //main method

private:
	void draw_help(Space& space, int x, int y); //if help turned on
	void draw_space(IPiece* piece, Coord& crd); //chessboard display
	void right_banner(); //options display
	void status_bar(std::string& stat); //game result display
	void play_sound(Game gm); //game result display

	RenderWindow window;
	Texture texture, t_board, t_help, t_voice; //texture for space and other, separate texture for background and helper, volume display
	Sprite sprite, sp_board, sp_help, hint, sp_voice; //sprite for space and other, separate sprite for background and helper, hint (example for help)
	Vector2i v2i; //for pulling out coordinates
	Color c_beat, c_move, c_keep, c_spec;//color for different situations
	SoundBuffer sb; //buffer
	Sound sound; //sound for audio files
	Font font; //font for text
	Text text; //text to display hint and status
	bool hold, help, volume, start; //pressed left mouse key, help turn on, voice, start new game
};
