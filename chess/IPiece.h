#pragma once

#include <cmath>

class IPiece
{
public:
	IPiece() = default;
	virtual ~IPiece() = default;

	virtual bool move_to(int x, int y) const = 0;

	void setX(int a) { x = a; }
	void setY(int a) { y = a; }
	int getX() const { return x; }
	int getY() const { return y; }
	void setPlayer(bool frs) { first_player = frs; }
	bool getPlayer() const { return first_player; }

private:
	int x = 0;
	int y = 0;
	bool first_player = true;

};

struct Space
{
	IPiece *cell = nullptr;
};
