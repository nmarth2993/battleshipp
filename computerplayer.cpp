#include "computerplayer.hpp"

computerplayer::computerplayer()
{
    srand(time(NULL));
}

void computerplayer::updatePlayer(position pos, bool hit, char initial, std::string boatName, bool sunk, bool gameOver, bool tooManyTurns, int turns)
{
    updateGrid(pos, hit, initial);
}

std::string computerplayer::playerName() const
{
    return "Computer Player";
}

void computerplayer::startGame()
{
    initializeGrid();
}

position computerplayer::shoot()
{
    for (;;)
    {
        position pos(rand() % GRID_SIZE, rand() % GRID_SIZE);
        if (getGrid().empty(pos))
        {
            return pos;
        }
    }
}