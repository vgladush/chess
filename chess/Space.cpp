#include "Space.h"

Space::Space(IPiece* piece) : cell(piece), move(Move::free) { }

Space::~Space()
{
    delete cell;
    cell = nullptr;
}

void Space::setMove(Move mv) { move = mv; }

Move Space::getMove() { return move; }

void Space::setPiece(IPiece* cl) { cell = cl; }

IPiece *Space::getPiece() { return cell; }
