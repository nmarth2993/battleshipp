#ifndef COMPUTER_PLAYER
#define COMPUTER_PLAYER

#include <random>

#include "player.hpp"

class computerplayer : public BattleshipPlayer
{
public:
    computerplayer();
    virtual ~computerplayer();

    void updatePlayer(position pos, bool hit, char initial, std::string boatName, bool sunk, bool gameOver, bool tooManyTurns, int turns);
    std::string playerName() const;
    void startGame();
    position shoot() const;

    // TODO: figure out how to do polymorphism

    // note: this class does not have a destructor
    // becuase this inherits a class with a virtual dtor
};

#endif