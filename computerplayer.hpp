#ifndef COMPUTER_PLAYER
#define COMPUTER_PLAYER

#include <time.h>
#include <random>

#include "player.hpp"

class computerplayer : public BattleshipPlayer
{
private:
    /* data */
public:
    computerplayer();

    void updatePlayer(position pos, bool hit, char initial, std::string boatName, bool sunk, bool gameOver, bool tooManyTurns, int turns);
    std::string playerName() const;
    void startGame();
    position shoot();

    ~computerplayer();
};

#endif