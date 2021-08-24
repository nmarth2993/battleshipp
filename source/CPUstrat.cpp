#include <iostream>
#include <iomanip>

#include <time.h> // for seeding random

#include "strategy/include/computerstrategy.hpp"
#include "include/playerevaluator.hpp"
#include "include/computerplayer.hpp"

int main(int argc, const char *argv[])
{
    srand(time(NULL));

    int runs = 100;
    std::cout << "running " << runs << " games\n";

    // std::cout << "alloc'd computer player at addr: " << computer << '\n';

    computerstrategy *computer = new computerstrategy();
    std::cout << "player name: " << computer->playerName() << '\n';
    std::cout << "made by: " << computer->author() << '\n';

    PlayerEvaluator evaluator(computer, runs);
    std::cout << "min: " << evaluator.minTurns() << " max: " << evaluator.maxTurns() << " avg: " << evaluator.averageTurns() << '\n';
    std::cout << "------\n";
    std::cout << "Simple hunt algorithm: ~65 shots average\n";
    std::cout << "This strategy: " << evaluator.averageTurns() << " shots average\n";
    std::cout << "==> " << std::round(((65.f - evaluator.averageTurns()) / 65.f * 100.f)) << "% less shots on average\n";

    delete computer;
    computer = nullptr;

    if (evaluator.minTurns() == 17)
    {
        std::cout << "You hit a perfect game!\n";
    }

    return 0;
}