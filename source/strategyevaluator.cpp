#include <iostream>

#include <time.h> // for seeding random

#include "../include/playerevaluator.hpp"
#include "../include/computerplayer.hpp"
#include "../include/player.hpp"

int main(int argc, const char *argv[])
{
    srand(time(NULL));

    int runs = 10;
    std::cout << "running " << runs << " games\n";

    // std::cout << "alloc'd computer player at addr: " << computer << '\n';

    computerplayer *computer = new computerplayer();
    std::cout << "player name: " << computer->playerName() << '\n';

    // std::cout << "calling computerplayer name: " << computer->computerplayer::playerName() << '\n';

    PlayerEvaluator evaluator(*computer, runs);
    std::cout << "min: " << evaluator.minTurns() << " max: " << evaluator.maxTurns() << " avg: " << evaluator.averageTurns() << '\n';

    delete computer;
    computer = nullptr;

    if (evaluator.minTurns() == 17)
    {
        std::cout << "You hit a perfect game!\n";
    }

    return 0;
}

// FIXME: as of right now, it seems that the base class dtor (BattleshipPlayer) is
// being called twice... once before the computerplayer (derived class) dtor (?????)
// and then another time as expected when the computer player class is deleted