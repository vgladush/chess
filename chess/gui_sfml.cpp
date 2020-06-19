#include "gui_sfml.h"
#include "Space.h"
#include <iostream>

Gui_sfml::Gui_sfml() : hold(false), mvx(0), mvy(0)
{
	window.create(VideoMode(WIDTH, HEIGHT), "Chess (C++ with SFML)", Style::Close);
	t_board.loadFromFile("resource/board.jpg");
	sp_board.setTexture(t_board);
	sp_board.setPosition(147, 0);
	texture.loadFromFile("resource/pieces.png");
	sprite.setTexture(texture);
	sprite.scale(0.240f, 0.240f);
}

Gui_sfml::~Gui_sfml()
{
}

void Gui_sfml::draw_board(Space space[8][8], int& x, int& y, int& xp, int& yp)
{
	while (window.isOpen())
	{
		Event event;
		v2i = Mouse::getPosition(window);
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed)
			{
				if (event.key.code == Mouse::Left)
				{
					mvx = x = (v2i.x - LEFT) / GRID;
					mvy = y = (v2i.y - TOP) / GRID;
					if (v2i.x >= LEFT && v2i.y >= TOP && 0 <= x < 8 && 0 <= y < 8 && space[x][y].getPiece())
						hold = true;
				}
			}
			if (event.type == Event::MouseButtonReleased)
			{
				if (event.key.code == Mouse::Left && hold)
				{
					xp = v2i.x;
					yp = v2i.y;
					hold = false;
				}
			}
		}
		window.clear(Color(210, 210, 210));
		window.draw(sp_board);
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				if (space[i][j].getPiece())
					draw_space(space[i][j].getPiece(), i, j);
			}
		}
		if (hold)
			draw_space(space[x][y].getPiece(), x, y);
		window.display();
	}
}

void Gui_sfml::draw_space(IPiece* piece, int x, int y)
{
	int color = (piece->getPlayer() ? WHITE : BLACK);
	int name = (int)piece->getName() * SIZE;
	sprite.setTextureRect(IntRect(name, color, SIZE, SIZE));
	if (hold && x == mvx && y == mvy)
		sprite.setPosition(v2i.x - GRID / 2, v2i.y - GRID / 2);
	else
		sprite.setPosition(LEFT + GRID * x, TOP + GRID * y);
	window.draw(sprite);
}
