#include "Space.h"

Space::Space(IPiece* piece) : cell(piece)
{
}

Space::~Space()
{
}

void Space::clear()
{
    if (cell)
        delete cell;
}

bool Space::chek_take(int x, int y, int xp, int yp) const
{
    return false;
}

bool Space::check_way(int x, int y, int xp, int yp) const
{
    return false;
}

void Space::setPiece(IPiece* cl)
{
    cell = cl;
}

IPiece *Space::getPiece()
{
    return cell;
}
