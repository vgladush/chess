#include "gui_sfml.h"
#include "Space.h"
#include <iostream>

Gui_sfml::Gui_sfml() : hold(false), help(false)
{
	window.create(VideoMode(WIDTH, HEIGHT), "Chess (C++ with SFML)", Style::Close);
	t_board.loadFromFile("resource/board.jpg"); //loading background
	sp_board.setTexture(t_board);
	t_help.loadFromFile("resource/helper.png"); //loading toggle button
	sp_help.setTexture(t_help);
	sp_help.scale(0.180f, 0.180f); //the size of the toggle button relative to the picture
	sp_help.setPosition(730, 150);
	sp_help.setTextureRect(IntRect(90, 990, 1480, 570));
	texture.loadFromFile("resource/pieces.png"); //loading of a picture of pieces for their further cutting
	sprite.setTexture(texture);
	sprite.scale(0.240f, 0.240f); //the size of the piece relative to the picture
}

Gui_sfml::~Gui_sfml() { }

Game Gui_sfml::draw_board(Space space[8][8], Coord& cd, std::string& err)
{
	while (window.isOpen())
	{
		Event event;
		v2i = Mouse::getPosition(window); //pull out mouse coordinates
		while (window.pollEvent(event)) //catch events
		{
			if (event.type == Event::Closed)
			{
				window.close();
				return Game::exit;
			}
			if (event.type == Event::MouseButtonPressed) // if pressed:
			{
				if (event.key.code == Mouse::Left) // left mouse button
				{
					cd.x = (v2i.x - INDENT) / GRID;
					cd.y = (v2i.y - INDENT) / GRID;
					std::cout << "take " << cd.x << " " << cd.y << std::endl;
					if (v2i.x >= INDENT && v2i.y >= INDENT && 0 <= cd.x && cd.x < 8 && 0 <= cd.y && cd.y < 8 && space[cd.x][cd.y].getPiece())
					{
						hold = true;
						return Game::hold;
					}
					if (sp_help.getGlobalBounds().contains(v2i.x, v2i.y))
					{
						help = !help;
						if (help)
							sp_help.setTextureRect(IntRect(90, 50, 1480, 570));
						else
							sp_help.setTextureRect(IntRect(90, 990, 1480, 570));
						return Game::helper;
					}
				}
			}
			if (event.type == Event::MouseButtonReleased) // if released:
			{
				if (event.key.code == Mouse::Left && hold) // left mouse button
				{
					cd.i = (v2i.x - INDENT) / GRID;
					cd.j = (v2i.y - INDENT) / GRID;
					std::cout << "relesed " << cd.i << " " << cd.j << std::endl;
					hold = false;
					if ((cd.x != cd.i || cd.y != cd.j) && v2i.x > INDENT && v2i.y > INDENT && cd.i < 8 && 8 > cd.j)
						return Game::relesed;
					else
						return Game::clear;
				}
			}
		}
		window.clear(Color(210, 210, 210)); //background color
		window.draw(sp_board); //background image
		window.draw(sp_help); //help toggle button
		Coord ext{ cd.x, cd.y };
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				ext.i = i;
				ext.j = j;
				if (space[i][j].getMove() != Move::free)
					draw_help(space[i][j], i, j);
				if (space[i][j].getPiece())
					draw_space(space[i][j].getPiece(), ext);
			}
		}
		ext = { cd.x, cd.y, cd.x, cd.y };
		if (hold) //layer on top
			draw_space(space[cd.x][cd.y].getPiece(), ext);
		window.display();
	}
	return Game::exit;
}

void Gui_sfml::draw_help(Space& space, int x, int y)
{
	//highlighting moves
	RectangleShape rect(Vector2f(GRID, GRID));
	rect.setPosition(IND + GRID * x, IND + GRID * y);
	if (space.getMove() == Move::beat)
		rect.setFillColor(Color(240, 90, 150, 90));
	else if (space.getMove() == Move::stay)
		rect.setFillColor(Color(210, 150, 0, 90));
	else
		rect.setFillColor(Color(60, 180, 180, 90));
	window.draw(rect);
}

void Gui_sfml::draw_space(IPiece* piece, Coord& crd)
{
	//drawing a piece
	int color = (piece->getPlayer() ? WHITE : BLACK);
	int name = (int)piece->getName() * SIZE;
	sprite.setTextureRect(IntRect(name, color, SIZE, SIZE));
	if (hold && crd.x == crd.i && crd.y == crd.j) //moving piece
		sprite.setPosition(v2i.x - GRID / 2, v2i.y - GRID / 2);
	else // standing piece
		sprite.setPosition(INDENT + GRID * crd.i, INDENT + GRID * crd.j);
	window.draw(sprite);
}
