#include "computerplayer.hpp"

computerplayer::computerplayer()
{
    // not seeding random here because if I do then
    // there is the possibility that if a computer player plays a game
    // and is destroyed and re-created to play another game
    // within one second, the seed will remain the same, causing the same game
    // to be played again
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
    std::cout << "startgame called, init grid\n";
    initializeGrid();
}

position computerplayer::shoot() const
{
    // std::cout << "---grid---\n";
    // for (int i = 0; i < GRID_SIZE; i++)
    // {
    //     for (int j = 0; j < GRID_SIZE; j++)
    //     {
    //         if (getGrid()->empty(position(i, j)))
    //         {
    //             std::cout << ". ";
    //         }
    //         else if (getGrid()->miss(position(i, j)))
    //         {
    //             std::cout << "* ";
    //         }
    //         else
    //         {
    //             std::cout << getGrid()->boatInitial(position(i, j)) << ' ';
    //         }
    //     }
    //     std::cout << '\n';
    // }
    // std::cout << "----------\n";

    for (;;)
    {
        position pos(rand() % GRID_SIZE, rand() % GRID_SIZE);
        if (getGrid()->empty(pos))
        {
            std::cout << "shooting at " << pos << '\n';
            return pos;
        }
    }
}

computerplayer::~computerplayer()
{
    std::cout << "dtor\n";
}