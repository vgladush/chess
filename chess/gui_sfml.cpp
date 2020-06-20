#include "gui_sfml.h"
#include "Space.h"
#include <iostream>

Gui_sfml::Gui_sfml() : hold(false), mvx(0), mvy(0)
{
	window.create(VideoMode(WIDTH, HEIGHT), "Chess (C++ with SFML)", Style::Close);
	t_board.loadFromFile("resource/board.jpg");
	sp_board.setTexture(t_board);
	texture.loadFromFile("resource/pieces.png");
	sprite.setTexture(texture);
	sprite.scale(0.240f, 0.240f);
}

Gui_sfml::~Gui_sfml() { }

bool Gui_sfml::draw_board(Space space[8][8], int& x, int& y, int& xp, int& yp, bool& help, std::string& err)
{
	while (window.isOpen())
	{
		Event event;
		v2i = Mouse::getPosition(window);
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				return false;
			}
			if (event.type == Event::MouseButtonPressed)
			{
				if (event.key.code == Mouse::Left)
				{
					mvx = x = (v2i.x - INDENT) / GRID;
					mvy = y = (v2i.y - INDENT) / GRID;
					std::cout << "take " << mvx << " " << mvy << std::endl;
					if (v2i.x >= INDENT && v2i.y >= INDENT && 0 <= x && x < 8 && 0 <= y && y < 8 && space[x][y].getPiece())
						hold = true;
				}
			}
			if (event.type == Event::MouseButtonReleased)
			{
				if (event.key.code == Mouse::Left && hold)
				{
					xp = (v2i.x - INDENT) / GRID;
					yp = (v2i.y - INDENT) / GRID;
					hold = false;
					std::cout << "relesed " << mvx << " " << mvy << std::endl;
					if ((x != xp || y != yp) && v2i.x > INDENT && v2i.y > INDENT && xp < 8 && 8 > yp)
						return true;
				}
			}
		}
		window.clear(Color(210, 210, 210));
		window.draw(sp_board);
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				if (help)
					draw_help(space[i][j], i, j);
				if (space[i][j].getPiece())
					draw_space(space[i][j].getPiece(), i, j);
			}
		}
		if (hold)
			draw_space(space[x][y].getPiece(), x, y);
		window.display();
	}
	return false;
}

void Gui_sfml::draw_help(Space& space, int x, int y)
{
	if (space.getMove() == Move::free)
		return;
	RectangleShape rect(Vector2f(GRID, GRID));
	rect.setPosition(IND + GRID * x, IND + GRID * y);
	if (space.getMove() == Move::bit)
		rect.setFillColor(Color(240, 30, 30, 75));
	else if (space.getMove() == Move::stay)
		rect.setFillColor(Color(210, 150, 0, 75));
	else
		rect.setFillColor(Color(60, 180, 180, 75));
	window.draw(rect);
}

void Gui_sfml::draw_space(IPiece* piece, int x, int y)
{
	int color = (piece->getPlayer() ? WHITE : BLACK);
	int name = (int)piece->getName() * SIZE;
	sprite.setTextureRect(IntRect(name, color, SIZE, SIZE));
	if (hold && x == mvx && y == mvy)
		sprite.setPosition(v2i.x - GRID / 2, v2i.y - GRID / 2);
	else
		sprite.setPosition(INDENT + GRID * x, INDENT + GRID * y);
	window.draw(sprite);
}
