//
// Created by Brian on 4/1/2016.
//

#include <iomanip>
#include "Game.h"
#include "Advantage.h"

namespace Gaming {
    const char Advantage::ADVANTAGE_ID = 'D';
    const double Advantage::ADVANTAGE_MULT_FACTOR = 2.0;

    Gaming::Advantage::Advantage(const Game &g, const Position &p, double capacity) : Resource(g,p,capacity*ADVANTAGE_MULT_FACTOR){ }

    Advantage::~Advantage() { }

    void Advantage::print(std::ostream &os) const {
        os << ADVANTAGE_ID << /*std::left << std::setw(4) <<*/ __id;
    }

    double Advantage::getCapacity() const {
        return __capacity;
    }

    double Advantage::consume() {
        finish();
        return __capacity;
    }

}
