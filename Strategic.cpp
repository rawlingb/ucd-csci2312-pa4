//
// Created by Brian on 4/1/2016.
//

#include <iomanip>
#include "Game.h"
#include "Strategy.h"
#include "Strategic.h"


namespace Gaming {
    const char Strategic::STRATEGIC_ID = 'T';

    Strategic::Strategic(const Game &g, const Position &p, double energy, Strategy *s) :
        Agent(g, p, energy), __strategy(s){ }

    Strategic::~Strategic() { delete __strategy; }

    ActionType Strategic::takeTurn(const Surroundings &s) const {
        return (*__strategy)(s);
    }

    void Strategic::print(std::ostream &os) const {
        os << STRATEGIC_ID << /*std::left << std::setw(4)  <<*/ __id;
    }
}


