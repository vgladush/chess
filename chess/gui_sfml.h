#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class Gui_sfml
{
public:
	Gui_sfml();
	~Gui_sfml();

private:
	RenderWindow window;
	Event event;
	Texture texture;
	Sprite sprite;
};
