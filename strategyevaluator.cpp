#include <iostream>

#include "playerevaluator.hpp"
#include "computerplayer.hpp"
#include "player.hpp"

int main(int argc, const char *argv[])
{
    int runs = 1;
    std::cout << "running " << runs << " games\n";

    computerplayer *computer = new computerplayer();

    // std::cout << "alloc'd computer player at addr: " << computer << '\n';

    PlayerEvaluator evaluator(*computer, runs);
    std::cout << "min: " << evaluator.minTurns() << " max: " << evaluator.maxTurns() << " avg: " << evaluator.averageTurns();

    delete computer;
    computer = nullptr;

    if (evaluator.minTurns() == 17)
    {
        std::cout << "You hit a perfect game!\n";
    }

    return 0;
}