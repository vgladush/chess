#pragma once

#include <cmath>

//enum to determine the type of piece
enum class Name
{
	king = 0,
	queen,
	bishop,
	knight,
	rook,
	pawn
};

//coordinates x, y, changed x and y 
struct Coord
{
	int x, y, i, j;
};

class IPiece
{
public:

	IPiece(bool player, Name tp) { first_player = player; type = tp; }
	virtual ~IPiece() = default;
	virtual bool move_to(Coord& cd) const = 0; //check, can move
	virtual bool to_take(Coord& cd) const = 0; //check, can take
	void setPlayer(bool player) { first_player = player; }
	bool getPlayer() const { return first_player; }
	void setName(bool player) { first_player = player; }
	Name getName() const { return type; }

private:

	Name type; //type of piece
	bool first_player = true; // white or black

};
