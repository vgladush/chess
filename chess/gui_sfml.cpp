#include "gui_sfml.h"

Gui_sfml::Gui_sfml()
{
	window.create(VideoMode(1024, 768), "Chess (C++ with SFML)", Style::Close);
	texture.loadFromFile("resource/board.jpg");
	sprite.setTexture(texture);
	sprite.setPosition(147, 0);
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear(Color(255, 255, 255));
		window.draw(sprite);
		window.display();
	}
}

Gui_sfml::~Gui_sfml()
{
}
