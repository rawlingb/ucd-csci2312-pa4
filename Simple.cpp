//
// Created by Brian on 4/1/2016.
//

#include <iomanip>
#include "Simple.h"

namespace Gaming {
    const char Simple::SIMPLE_ID ='S';

    Simple::Simple(const Game &g, const Position &p, double energy) : Agent(g, p, energy) { }

    Simple::~Simple(){ }

    ActionType Simple::takeTurn(const Surroundings &s) const {
        int strategy = 0;
        PositionRandomizer pr;
        while (strategy < 2) {
            std::vector<int> resource(0);
            //ActionType resource[9];
            //int size = 0;
            for (int i = 0; i < 9; i++) {
                if ((s.array[i] == FOOD || s.array[i] == ADVANTAGE) && strategy == 0) {
                    resource.push_back(i);
                } else if ((s.array[i] == EMPTY) && strategy == 1) {
                    resource.push_back(i);
                }
            }
            //Randomizer
            if(resource.size() > 0 ) {
                Position pos = pr(resource);
                if (pos.x == 1 && pos.y == 1)
                    return ActionType::STAY;
                else if (pos.x == 1 && pos.y == 0)
                    return ActionType::W;
                else if (pos.x == 1 && pos.y == 2)
                    return ActionType::E;
                else if (pos.x == 2 && pos.y == 0)
                    return ActionType::SW;
                else if (pos.x == 0 && pos.y == 0)
                    return ActionType::NW;
                else if (pos.x == 0 && pos.y == 1)
                    return ActionType::N;
                else if (pos.x == 2 && pos.y == 1)
                    return ActionType::S;
                else if (pos.x == 2 && pos.y == 2)
                    return ActionType::SE;
                else if (pos.x == 0 && pos.y == 2)
                    return ActionType::NE;
                //std::default_random_engine __gen;
                //std::uniform_int_distribution<int> d(0, size);
                //return resource[d(__gen)];
            }
            strategy++;
        }
        return STAY;
    }

    void Simple::print(std::ostream &os) const {
        os << SIMPLE_ID << /*std::left << std::setw(4)  <<*/ __id;
    }
};