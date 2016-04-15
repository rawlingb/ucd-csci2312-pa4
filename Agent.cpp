//
// Created by Brian on 4/1/2016.
//

#include "Game.h"
#include "Agent.h"
#include "Resource.h"

namespace Gaming {
    const double Agent::AGENT_FATIGUE_RATE = 0.3;

    Agent::Agent(const Game &g, const Position &p, double energy) : Piece(g, p), __energy(energy){ }

    Agent::~Agent() { }

    void Agent::age() { __energy -= AGENT_FATIGUE_RATE; }

    Piece &Agent::operator*(Piece &other) { return other.interact(this); };

    Piece &Agent::interact(Agent *other) {
        if(getEnergy() > other->getEnergy()) {
            other->finish();
        } else if (getEnergy() < other->getEnergy()) {
            finish();
        } else if (getEnergy() == other->getEnergy()) {
            finish();
            other->finish();
        }
        return *this;//Does it matter what I return?
    }

    Piece &Agent::interact(Resource *other) {
        __energy += other->consume();//Is this the right function?
        return *this;
    }
}


