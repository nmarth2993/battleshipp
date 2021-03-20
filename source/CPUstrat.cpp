#include <iostream>

#include <time.h> // for seeding random

#include "strategy/include/computerstrategy.hpp"
#include "include/playerevaluator.hpp"
#include "include/computerplayer.hpp"

int main(int argc, const char *argv[])
{
    srand(time(NULL));

    int runs = 500;
    std::cout << "running " << runs << " games\n";

    // std::cout << "alloc'd computer player at addr: " << computer << '\n';

    computerstrategy *computer = new computerstrategy();
    std::cout << "player name: " << computer->playerName() << '\n';
    std::cout << "made by: " << computer->author() << '\n';

    PlayerEvaluator evaluator(computer, runs);
    std::cout << "min: " << evaluator.minTurns() << " max: " << evaluator.maxTurns() << " avg: " << evaluator.averageTurns() << '\n';

    delete computer;
    computer = nullptr;

    if (evaluator.minTurns() == 17)
    {
        std::cout << "You hit a perfect game!\n";
    }

    return 0;
}