#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define WIDTH 1024
#define HEIGHT 768

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
