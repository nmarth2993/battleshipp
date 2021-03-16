#include <iostream>

#include "player.hpp"
#include "game.hpp"

int main(int argc, const char *argv[])
{
    BattleshipPlayer *player = new BattleshipPlayer();
    BattleshipGame game(player);
    game.play();

    delete player;
    player = nullptr;

    return 0;
}