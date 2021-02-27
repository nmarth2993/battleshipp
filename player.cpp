#include <iostream>
#include <limits>

#define UPPER_BIT (1 << 5)
#define UPPER_A 0x41
#define UPPER_Z 0x5A

#define IS_UPPER(c) (c >= UPPER_A && c <= UPPER_Z)
#define IN_RANGE(n) (n >= 1 && n <= 10)

#define NUM_HEADER "\n   1 2 3 4 5 6 7 8 9 10\n"

#include "player.hpp"

BattleshipPlayer::BattleshipPlayer()
{
}

void BattleshipPlayer::startGame()
{
    // create grid
    initializeGrid();

    if (this->m_name.empty())
    {
        std::cout << "Enter your name: ";
        std::getline(std::cin, m_name);
    }
}
std::string BattleshipPlayer::playerName() const
{
    return m_name;
}
position BattleshipPlayer::shoot() const
{
    bool error = false;
    char row;
    int col;

    do
    {
        error = false;
        std::cout << "Enter a row to shoot at (A-J): ";

        std::cin >> row;
        // make input uppercase
        row &= ~UPPER_BIT;

        if (std::cin.fail() || !IS_UPPER(row))
        {
            std::cout << "Unrecognized input\n";
            error = true;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (error);

    do
    {
        error = false;
        std::cout << "Enter a column to shoot at (1-10): ";

        std::cin >> col;

        if (std::cin.fail() || !IN_RANGE(col))
        {
            std::cout << "Unrecognized input\n";
            error = true;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (error);

    return position(row, col);
}

void BattleshipPlayer::updateGrid(position pos, bool hit, char initial)
{
    grid.shotAt(pos, hit, initial);
}

BattleshipGrid BattleshipPlayer::getGrid() const
{
    return grid;
}

void BattleshipPlayer::initializeGrid()
{
    grid = BattleshipGrid();
}
void BattleshipPlayer::updatePlayer(position pos, bool hit, char initial, std::string boatName, bool sunk, bool gameOver, bool tooManyTurns, int turns)
{
    std::cout << "Turn #" << turns << ": Your shot at " << pos;
    if (hit)
    {
        std::cout << " hit the " << boatName << (sunk ? " and sunk it." : "");
    }
    else
    {
        std::cout << " was a miss";
    }
    std::cout << '\n';

    if (gameOver)
    {
        std::cout << "The game is over. ";
    }
    if (tooManyTurns)
    {
        std::cout << "The game has gone on too long.";
    }
    updateGrid(pos, hit, initial);

    std::cout << NUM_HEADER;
    for (int i = 0; i < GRID_SIZE; i++)
    {
        std::cout << (char)('A' + i) << "  ";
        for (int j = 0; j < GRID_SIZE; j++)
        {
            position gridpos(i, j);
            std::cout << (grid.empty(gridpos) ? SYMBOL_EMPTY : grid.miss(gridpos) ? SYMBOL_MISS
                                                                                  : grid.boatInitial(gridpos));
            if (j == GRID_SIZE - 1)
            {
                std::cout << '\n';
            }
        }
    }
}

BattleshipPlayer::~BattleshipPlayer()
{
}