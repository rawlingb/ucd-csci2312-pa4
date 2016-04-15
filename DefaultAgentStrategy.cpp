//
// Created by Brian on 4/1/2016.
//

#include "Gaming.h"
#include "DefaultAgentStrategy.h"

namespace Gaming {
    DefaultAgentStrategy::DefaultAgentStrategy() { }

    DefaultAgentStrategy::~DefaultAgentStrategy() { }

    ActionType Gaming::DefaultAgentStrategy::operator()(const Surroundings &s) const {
        int strategy = 0;
        bool out = false;
        PositionRandomizer pr;
        while (strategy < 4) {
            //int resource[9];
            std::vector<int> resource(0);
            //int size = 0;
            for (int i = 0; i < 9; i++) {
                if ((s.array[i] == ADVANTAGE) && strategy == 0) {
                    resource.push_back(i);
                } else if ((s.array[i] == FOOD) && strategy == 1) {
                    resource.push_back(i);
                } else if ((s.array[i] == EMPTY) && strategy == 2) {
                    resource.push_back(i);
                } else if ((s.array[i] == SIMPLE) && strategy == 3) {
                    resource.push_back(i);
                }
            }
            //Randomizer
            if (resource.size() > 0) {
                Position pos = pr(resource);
                if (pos.x == 1 && pos.y == 1) return ActionType::STAY;
                else if (pos.x == 1 && pos.y == 0) return ActionType::W;
                else if (pos.x == 1 && pos.y == 2) return ActionType::E;
                else if (pos.x == 2 && pos.y == 0) return ActionType::SW;
                else if (pos.x == 0 && pos.y == 0) return ActionType::NW;
                else if (pos.x == 0 && pos.y == 1) return ActionType::N;
                else if (pos.x == 2 && pos.y == 1) return ActionType::S;
                else if (pos.x == 2 && pos.y == 2) return ActionType::SE;
                else if (pos.x == 0 && pos.y == 2) return ActionType::NE;
            }
            strategy++;
        }
        return STAY;
    }



}


