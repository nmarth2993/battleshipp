#ifndef COMPUTER_PLAYER
#define COMPUTER_PLAYER

#include <random>

#include "player.hpp"

class computerplayer : public BattleshipPlayer
{
public:
    computerplayer();
    virtual ~computerplayer();

    virtual void updatePlayer(position pos, bool hit, char initial, std::string boatName, bool sunk, bool gameOver, bool tooManyTurns, int turns);
    virtual std::string playerName() const;
    virtual void startGame();
    virtual position shoot(); // not const to accomodate strategy

    // TODO: figure out how to do polymorphism

    // note: this class does not have a destructor
    // becuase this inherits a class with a virtual dtor
};

#endif