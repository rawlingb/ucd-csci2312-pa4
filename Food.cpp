//
// Created by Brian on 4/1/2016.
//

#include <iomanip>
#include "Game.h"
#include "Food.h"

namespace Gaming {
    const char Food::FOOD_ID = 'F';

    Food::Food(const Gaming::Game &g, const Gaming::Position &p, double capacity) : Resource(g,p,capacity) { }

    Food::~Food() { }

    void Food::print(std::ostream &os) const {
        os << FOOD_ID << /*std::left << std::setw(4) <<*/ __id;
    }


}

