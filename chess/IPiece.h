#pragma once

#include <cmath>

enum class Name
{
	king = 0,
	queen,
	bishop,
	knight,
	rook,
	pawn
};

class IPiece
{
public:

	IPiece(bool player, Name tp) { first_player = player; type = tp; }
	virtual ~IPiece() = default;

	virtual bool move_to(int x, int y, int xp, int yp) const = 0; //check, can move
	virtual bool to_take(int x, int y, int xp, int yp) const = 0; //check, can take
	void setPlayer(bool player) { first_player = player; }
	bool getPlayer() const { return first_player; }
	void setName(bool player) { first_player = player; }
	Name getName() const { return type; }

private:

	Name type;
	bool first_player = true; // white or black

};
