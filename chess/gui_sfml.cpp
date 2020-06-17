#include "gui_sfml.h"

Gui_sfml::Gui_sfml()
{
	window.create(VideoMode(WIDTH, HEIGHT), "Chess (C++ with SFML)", Style::Close);
	texture.loadFromFile("resource/pieces.png");
	sprite.setTexture(texture);
	sprite.setPosition(147, 0);
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear(Color(0, 255, 255));
		window.draw(sprite);
		window.display();
	}
}

Gui_sfml::~Gui_sfml()
{
}
