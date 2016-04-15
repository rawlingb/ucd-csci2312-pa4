//
// Created by Brian on 4/1/2016.
//

#include "AggressiveAgentStrategy.h"
#include "Game.h"

namespace Gaming {
    const double AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = Game::STARTING_AGENT_ENERGY * 0.75;

    AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy) : __agentEnergy(agentEnergy) { }

    AggressiveAgentStrategy::~AggressiveAgentStrategy() { }

    ActionType AggressiveAgentStrategy::operator()(const Surroundings &s) const {
        int strategy = 0;
        bool out = false;
        PositionRandomizer pr;
        while (strategy < 4) {
            std::vector<int> resource(0);
            if((strategy == 0 && __agentEnergy >= DEFAULT_AGGRESSION_THRESHOLD) || strategy > 0) {
            for (int i = 0; i < 9; i++) {
                if (((s.array[i] == STRATEGIC) || (s.array[i] == SIMPLE)) && strategy == 0) {
                    resource.push_back(i);
                } else if ((s.array[i] == ADVANTAGE) && strategy == 1) {
                    resource.push_back(i);
                } else if ((s.array[i] == FOOD) && strategy == 2) {
                    resource.push_back(i);
                } else if ((s.array[i] == EMPTY) && strategy == 3) {
                    resource.push_back(i);
                }
            }}
            //Randomizer
            if (resource.size() > 0) {
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
            }
            strategy++;
        }
        return STAY;
    }
}

