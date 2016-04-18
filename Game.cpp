//
// Created by Brian on 4/1/2016.
//

#include <iomanip>
#include <set>
#include <cassert>
#include "Game.h"
#include "Simple.h"
#include "Strategic.h"
#include "Resource.h"
#include "Food.h"
#include "Advantage.h"

namespace Gaming {
    const unsigned Game::MIN_WIDTH = 3, Game::MIN_HEIGHT = 3;
    const double Game::STARTING_AGENT_ENERGY = 20;
    const double Game::STARTING_RESOURCE_CAPACITY = 10;
    PositionRandomizer Game::__posRandomizer;
    const unsigned int Game::NUM_INIT_AGENT_FACTOR = 4;
    const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;

    Game::Game() : __width(MIN_WIDTH), __height(MIN_HEIGHT), __round(0), __status(Status::NOT_STARTED) {
        for (unsigned i = 0; i < MIN_WIDTH * MIN_HEIGHT; i++)
            __grid.push_back(nullptr);
    }

    Game::Game(unsigned width, unsigned height, bool manual) :
            __width(width), __height(height), __round(0), __status(Status::NOT_STARTED) {
        if(__width < MIN_WIDTH || __height < MIN_HEIGHT) throw InsufficientDimensionsEx(MIN_WIDTH, MIN_HEIGHT, __width, __height);
        for (unsigned i = 0; i < width * height; i++)
            __grid.push_back(nullptr);
        if (!manual)
            populate();
    }

    Game::~Game() {
        for (Piece *p : __grid) {
            if (p != nullptr) {
                delete p;
                p = nullptr;
            }
        }
    }

    unsigned int Game::getNumPieces() const {
        unsigned numPieces = 0;
        for (Piece *p: __grid) {
            if (p != nullptr)
                ++numPieces;
        }
        return numPieces;
    }

    unsigned int Game::getNumAgents() const {
        unsigned numPieces = 0;
        for (Piece *p: __grid) {
            Agent *a = dynamic_cast<Agent *>(p);
            if (a)
                ++numPieces;
        }
        return numPieces;
    }

    unsigned int Game::getNumSimple() const {
        unsigned numPieces = 0;
        for (Piece *p: __grid) {
            Simple *s = dynamic_cast<Simple *>(p);
            if (s)
                ++numPieces;
        }
        return numPieces;
    }

    unsigned int Game::getNumStrategic() const {
        unsigned numPieces = 0;
        for (Piece *p: __grid) {
            Strategic *s = dynamic_cast<Strategic *>(p);
            if (s)
                ++numPieces;
        }
        return numPieces;
    }

    unsigned int Game::getNumResources() const {
        unsigned numPieces = 0;
        for (Piece *p: __grid) {
            Resource *r = dynamic_cast<Resource *>(p);
            if (r)
                ++numPieces;
        }
        return numPieces;
    }

    const Piece *Game::getPiece(unsigned int x, unsigned int y) const { //Ex, x = 3, y = 3, max = 2, (0,0)
        if(__grid[(x * __width) + y] == nullptr) throw PositionEmptyEx(x, y);
        return __grid[(x * __width) + y];
    }

    void Game::addSimple(const Position &position) {
        if(position.x >= __height || position.y >= __width) throw OutOfBoundsEx( __width,__height, position.y, position.x);
        if (__grid[(position.x * __width) + position.y] == nullptr) {
            __grid[(position.x * __width) + position.y] = new Simple(*this, position, STARTING_AGENT_ENERGY);
        } else throw PositionNonemptyEx(position.x, position.y);
    }

    void Game::addSimple(const Position &position, double energy) {
        if(position.x >= __height || position.y >= __width) throw OutOfBoundsEx( __width,__height, position.y, position.x);
        if (__grid[(position.x * __width) + position.y] == nullptr) {
            __grid[(position.x * __width) + position.y] = new Simple(*this, position, energy);
        } else throw PositionNonemptyEx(position.x, position.y);
    }

    void Game::addSimple(unsigned x, unsigned y) {
        if(x >= __height || y >= __width) throw OutOfBoundsEx( __width,__height, y, x);
        if (__grid[(x * __width) + y] == nullptr) {
            __grid[(x * __width) + y] = new Simple(*this, Position(x, y), STARTING_AGENT_ENERGY);
        } else throw PositionNonemptyEx(x, y);
    }

    void Game::addSimple(unsigned x, unsigned y, double energy) {
        if(x >= __height || y >= __width) throw OutOfBoundsEx( __width,__height, y, x);
        if (__grid[(x * __width) + y] == nullptr) {
            __grid[(x * __width) + y] = new Simple(*this, Position(x, y), energy);
        } else throw PositionNonemptyEx(x, y);
    }

    void Game::addStrategic(const Position &position, Strategy *s) {
        if(position.x >= __height || position.y >= __width) throw OutOfBoundsEx( __width,__height, position.y, position.x);
        if (__grid[(position.x * __width) + position.y] == nullptr) {
            __grid[(position.x * __width) + position.y] = new Strategic(*this, position, STARTING_AGENT_ENERGY, s);
        } else throw PositionNonemptyEx(position.x, position.y);
    }

    void Game::addStrategic(unsigned x, unsigned y, Strategy *s) {
        if(x >= __height || y >= __width) throw OutOfBoundsEx( __width,__height, y, x);
        if (__grid[(x * __width) + y] == nullptr) {
            __grid[(x * __width) + y] = new Strategic(*this, Position(x, y), STARTING_AGENT_ENERGY, s);
        } else throw PositionNonemptyEx(x, y);
    }

    void Game::addFood(const Position &position) {
        if(position.x >= __height || position.y >= __width) throw OutOfBoundsEx( __width,__height, position.y, position.x);
        if (__grid[(position.x * __width) + position.y] == nullptr) {
            __grid[(position.x * __width) + position.y] = new Food(*this, position, STARTING_RESOURCE_CAPACITY);
        } else throw PositionNonemptyEx(position.x, position.y);
    }

    void Game::addFood(unsigned x, unsigned y) {
        if(x >= __height || y >= __width) throw OutOfBoundsEx( __width,__height, y, x);
        if (__grid[(x * __width) + y] == nullptr) {
            __grid[(x * __width) + y] = new Food(*this, Position(x, y), STARTING_RESOURCE_CAPACITY);
        } else throw PositionNonemptyEx(x, y);
    }

    void Game::addAdvantage(const Position &position) {
        if(position.x >= __height || position.y >= __width) throw OutOfBoundsEx( __width,__height, position.y, position.x);
        if (__grid[(position.x * __width) + position.y] == nullptr) {
            __grid[(position.x * __width) + position.y] = new Advantage(*this, position, STARTING_RESOURCE_CAPACITY);
        } else throw PositionNonemptyEx(position.x, position.y);
    }

    void Game::addAdvantage(unsigned x, unsigned y) {
        if(x >= __height || y >= __width) throw OutOfBoundsEx( __width,__height, y, x);
        if (__grid[(x * __width) + y] == nullptr) {
            __grid[(x * __width) + y] = new Advantage(*this, Position(x, y), STARTING_RESOURCE_CAPACITY);
        } else throw PositionNonemptyEx(x, y);
    }

    // encoded as an array/vector top-left row-wise bottom-right
    // [0][1][2]   (-1,-1) (0,-1) (1,-1)
    // [3][4][5]   (-1, 0) (0, 0) (1, 0)
    // [6][7][8]   (-1, 1) (0, 1) (1, 1)
    // the piece is always at 1x1 (SELF)

    const Surroundings Game::getSurroundings(const Position &pos) const {
        Surroundings surroundings;
        for (unsigned i = 0; i < 3; i++) {
            for (unsigned j = 0; j < 3; j++) {
                if(i == 1 && j == 1)
                    surroundings.array[(i * 3) + j] = PieceType::SELF;
                else if (((pos.x + i) > 0 && (pos.x + i - 1) < __height) && ((pos.y + j) > 0 && (pos.y + j - 1) < __width)) {
                    try {
                        const Piece *p = getPiece((pos.x + i) - 1, (pos.y + j) - 1);
                        surroundings.array[(i * 3) + j] = p->getType();
                    } catch(PositionEmptyEx &p) {
                        surroundings.array[(i * 3) + j] = PieceType::EMPTY;
                    }
                } else {
                    surroundings.array[(i * 3) + j] = PieceType::INACCESSIBLE;
                }
            }
        }
        return surroundings;
    }

    //Y IS WIDTH AND X IS HEIGHT
    const ActionType Game::reachSurroundings(const Position &from, const Position &to) {
        if (from.x == to.x && from.y == to.y)
            return ActionType::STAY;
        else if (from.x == to.x && (from.y - 1) == to.y)
            return ActionType::W;
        else if (from.x == to.x && (from.y + 1) == to.y)
            return ActionType::E;
        else if ((from.x + 1) == to.x && (from.y - 1) == to.y)
            return ActionType::SW;
        else if ((from.x - 1) == to.x && (from.y - 1) == to.y)
            return ActionType::NW;
        else if ((from.x - 1) == to.x && (from.y) == to.y)
            return ActionType::N;
        else if ((from.x + 1) == to.x && (from.y) == to.y)
            return ActionType::S;
        else if ((from.x + 1) == to.x && (from.y + 1) == to.y)
            return ActionType::SE;
        else if ((from.x - 1) == to.x && (from.y + 1) == to.y)
            return ActionType::NE;
    }

    bool Game::isLegal(const ActionType &ac, const Position &pos) const {
        if (ac == ActionType::NW) return pos.x > 0 && pos.y > 0;
        else if (ac == ActionType::SW) return pos.x < (__height - 1) && pos.y > 0;
        else if (ac == ActionType::NE) return pos.x > 0 && pos.y < (__width - 1);
        else if (ac == ActionType::SE) return pos.x < (__height - 1) && pos.y < (__width - 1);
        else if (ac == ActionType::W) return pos.y > 0;
        else if (ac == ActionType::E) return pos.y < (__width - 1);
        else if (ac == ActionType::N) return pos.x > 0;
        else if (ac == ActionType::S) return pos.x < (__height - 1);
    }

    //Y IS WIDTH AND X IS HEIGHT
    const Position Game::move(const Position &pos, const ActionType &ac) const {
        if (isLegal(ac, pos)) {
            switch (ac) {
                case STAY:
                    return pos;
                case NW:
                    return Position(pos.x - 1, pos.y - 1);
                case N:
                    return Position(pos.x - 1, pos.y);
                case NE:
                    return Position(pos.x - 1, pos.y + 1);
                case W:
                    return Position(pos.x, pos.y - 1);
                case E:
                    return Position(pos.x, pos.y + 1);
                case SW:
                    return Position(pos.x + 1, pos.y - 1);
                case S:
                    return Position(pos.x + 1, pos.y);
                case SE:
                    return Position(pos.x + 1, pos.y + 1);
            }
        } else
            return pos;
    }

    void Game::populate() {
        __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
        __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
        unsigned int numStrategic = __numInitAgents / 2;
        unsigned int numSimple = __numInitAgents - numStrategic;
        unsigned int numAdvantages = __numInitResources / 4;
        unsigned int numFoods = __numInitResources - numAdvantages;

        std::default_random_engine gen;
        std::uniform_int_distribution<int> d(0, (__width * __height)-1);

        // populate Strategic agents
        while (numStrategic > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Strategic(*this, pos, Game::STARTING_AGENT_ENERGY);
                numStrategic--;
            }
        }

        // populate Simple agents
        while (numSimple > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Simple(*this, pos, Game::STARTING_AGENT_ENERGY);
                numSimple--;
            }
        }

        // populate Advantage
        while (numAdvantages > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Food(*this, pos, STARTING_RESOURCE_CAPACITY);
                numAdvantages--;
            }
        }

        // populate Food
        while (numFoods > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Food(*this, pos, STARTING_RESOURCE_CAPACITY);
                numFoods--;
            }
        }
    }

    std::ostream &operator<<(std::ostream &os, const Game &game) {
        os << "Round " << game.__round << std::endl;
        for (int j = 0; j < game.__height; j++) {
            for (int k = 0; k < game.__width; k++) {
                if(game.__grid[(j * game.__width) + k] != nullptr)
                    os << '[' << *(game.__grid[(j * game.__width) + k]) << ']';
                else
                    os << '[' <<  std::setw(5) << "     " << ']';
            }
            os << std::endl;
        }
        os << "Status: " << game.__status << std::endl;
        return os;
    }

    void Game::round() {
        if(__status == Status::NOT_STARTED) __status = Status::PLAYING;
        std::set<int> iset;
        for (unsigned int i = 0; i < __width*__height; ++i) {
            if(__grid[i] != nullptr)
                iset.insert(i);
        }
        for (auto it = iset.begin(); it != iset.end(); ) {
            Piece* p = __grid[*it];
            if(p->isViable() && !p->getTurned()) {
                p->setTurned(true);
                ActionType dir = p->takeTurn(getSurroundings(p->getPosition()));
                if(dir != ActionType::STAY) {
                    Position newPos = move(p->getPosition(),dir);
                    Piece *other = __grid[(newPos.x * __width) + newPos.y];
                    if(other != nullptr) {
                        (*p) * (*other);
                        if (!other->isViable() && !p->isViable()) {
                            delete __grid[(newPos.x * __width) + newPos.y];
                            __grid[(newPos.x * __width) + newPos.y] = nullptr;
                            delete p;
                            __grid[*it] = nullptr;
                            iset.erase(newPos.x*__width + newPos.y);
                            it = iset.erase(it);
                        } else if (!other->isViable() && p->isViable()) {
                            delete __grid[(newPos.x * __width) + newPos.y];
                            //__grid[(newPos.x * __width) + newPos.y] = nullptr;
                            //iset.erase(newPos);
                            p->setPosition(newPos);
                            __grid[newPos.x*__width + newPos.y] = __grid[*it];//
                            __grid[*it] = nullptr;//
                            it = iset.erase(it);
                            //++it;
                        } else if (other->isViable() && !p->isViable()) {
                            delete p;
                            __grid[*it] = nullptr;
                            it = iset.erase(it);
                        }
                    } else {
                        p->setPosition(newPos);
                        __grid[newPos.x*__width + newPos.y] = __grid[*it];//
                        __grid[*it] = nullptr;//
                        iset.insert(newPos.x*__width + newPos.y);
                        it = iset.erase(it);
                    }
                } else {
                    ++it;
                }
            } else {
                ++it;
            }
        }
        unsigned int i = 0;
        for (i = 0; i < __width*__height; ++i) {
            Piece *p = __grid[i];
            if(p != nullptr) {
                assert(__grid[(p->getPosition().x*__width) + p->getPosition().y] == __grid[i]);
                p->age();
                p->setTurned(false);
                if(dynamic_cast<Agent *>(p)){
                    if(dynamic_cast<Agent *>(p)->getEnergy() <= 0) {
                        delete __grid[i];
                        __grid[i] = nullptr;
                    }
                } if(__grid[i] != nullptr){
                    if(dynamic_cast<Resource *>(p)) {
                        if(dynamic_cast<Resource *>(p)->getCapacity() <= 0) {
                            delete __grid[i];
                            __grid[i] = nullptr;
                        }
                    }
                }
            }
        }
    }

    void Game::play(bool verbose) {
        do {
            if((getNumPieces() == 0) || (getNumResources() == 0))//(getNumPieces() == 1 && getNumAgents() == 1) || (getNumStrategic() == 0 && getNumResources() == 0))
                __status = Status::OVER;
            if(verbose)
                std::cout << *this << std::endl;
            round();
            __round++;
        } while (__status != Status::OVER);
    }


}