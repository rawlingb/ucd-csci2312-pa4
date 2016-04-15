//
// Created by Brian on 4/1/2016.
//

#include "Game.h"
#include "Agent.h"
#include "Resource.h"

namespace Gaming {
    const double Resource::RESOURCE_SPOIL_FACTOR = 1.2;

    Resource::Resource(const Gaming::Game &g, const Gaming::Position &p, double capacity) : Piece(g, p), __capacity(capacity){ }

    Resource::~Resource() { }

    void Resource::age() {
        __capacity -= RESOURCE_SPOIL_FACTOR;
    }

    double Resource::consume() {
        finish();
        return __capacity;
    }

    Piece &Resource::operator*(Piece &other) {
        return other.interact(this);
    }

    Piece &Resource::interact(Agent *other) {
        return other->interact(this);
    }

    Piece &Resource::interact(Resource *other) { //Should NEVER happen
        return *this;
    }

    ActionType Resource::takeTurn(const Surroundings &s) const { return STAY; }
}



