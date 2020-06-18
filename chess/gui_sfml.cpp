#include "gui_sfml.h"
#include "Space.h"

Gui_sfml::Gui_sfml()
{
	window.create(VideoMode(WIDTH, HEIGHT), "Chess (C++ with SFML)", Style::Close);
	t_board.loadFromFile("resource/board.jpg");
	sp_board.setTexture(t_board);
	sp_board.setPosition(147, 0);
	window.draw(sp_board);
	texture.loadFromFile("resource/pieces.png");
	sprite.setTexture(texture);
	sprite.scale(0.265f, 0.265f);
	//sprite.setTextureRect(IntRect(0, 330, 330, 330));
	//sprite.setPosition(198, 50);
	sprite.setTextureRect(IntRect(660, 330, 330, 330));
	sprite.setPosition(345, 50);
}

Gui_sfml::~Gui_sfml()
{
}

void Gui_sfml::draw_board(Space space[8][8], int& x, int& y, int& xp, int& yp)
{
	Event event;
	window.create(VideoMode(WIDTH, HEIGHT), "Chess (C++ with SFML)", Style::Close);
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear(Color(0, 255, 255));
		window.draw(sp_board);
		window.draw(sprite);
		window.display();
	}
}
