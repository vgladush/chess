#pragma once

#include <cmath>

class IPiece
{
public:

	IPiece(bool player) { first_player = player; }
	virtual ~IPiece() = default;

	virtual bool move_to(int x, int y, int xp, int yp) const = 0; //check, can move
	virtual bool to_take(int x, int y, int xp, int yp) const = 0; //check, can take
	void setPlayer(bool player) { first_player = player; }
	bool getPlayer() const { return first_player; }

private:
	bool first_player = true; // white or black

};
