#pragma once

#include <cmath>

class IPiece
{
public:
	IPiece() = default;
	virtual ~IPiece() = default;

	virtual bool move_to(int x, int y) = 0;

	void setX(int a) { x = a; }
	void setY(int a) { y = a; }
	int getX() { return x; }
	int getY() { return y; }
	void setPlayer(bool frs) { first_player = frs; }
	bool getPlayer() { return first_player; }

private:
	int x = 0;
	int y = 0;
	bool first_player = true;

};

struct Space
{
	IPiece *cell;
};
