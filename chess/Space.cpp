#include "Space.h"

Space::Space()
{
}

Space::~Space()
{
}

template<IPiece* piece>
bool Space::chek_take(int x, int y) const
{
    return false;
}

template<IPiece* piece>
bool Space::check_way(int x, int y) const
{
    return false;
}
