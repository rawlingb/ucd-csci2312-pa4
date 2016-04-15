//
// Created by Brian on 4/1/2016.
//

#include "Game.h"
#include "Piece.h"

namespace Gaming {
    unsigned int Piece::__idGen = 0;

    Piece::~Piece() { }

    Piece::Piece(const Game &g, const Position &p) : __game(g), __position(p), __finished(false), __turned(false) {
        __id = __idGen++;
    }

    std::ostream &operator<<(std::ostream &os, const Piece &piece) {
        piece.print(os);
        return os;
    }


}

