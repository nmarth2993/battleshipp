#ifndef BATTLESHIP_GAME
#define BATTLESHIP_GAME

#include "position.hpp"
#include "boat.hpp"
#include "grid.hpp"
#include "player.hpp"

class BattleshipGame
{
private:
    ocean *m_ocean;
    BattleshipPlayer m_player;
    int m_turns;

public:
    BattleshipGame(BattleshipPlayer player);

    int play();

    ~BattleshipGame();
};

#endif