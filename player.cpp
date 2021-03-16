#include <iostream>
#include <limits>

#define UPPER_BIT (1 << 5)
#define UPPER_A 'A'
#define UPPER_J 'J'

#define COL_IN_RANGE(c) (c >= UPPER_A && c <= UPPER_J)
#define ROW_IN_RANGE(n) (n >= 1 && n <= 10)

#define NUM_HEADER "\n   1 2 3 4 5 6 7 8 9 10\n"

#include "player.hpp"

BattleshipPlayer::BattleshipPlayer()
{
    std::cout << "ctor player\n";
    m_name = nullptr;
    grid = nullptr;
    // std::cout << "alloc'd player name at addr: " << m_name;
}

void BattleshipPlayer::startGame()
{
    // create grid
    initializeGrid(); // TODO: FOR SOME REASON THIS METHOD DOES NOT MODIFY
    std::cout << "grid addr: " << grid << '\n';

    std::cout << "dereferencing grid...\n";
    grid->empty(position(1, 1));
    std::cout << "called empty at (A, 1)\n";

    if (m_name == nullptr)
    {
        m_name = new std::string;
        std::cout << "Enter your name: ";
        std::getline(std::cin, *m_name);
    }
}
std::string BattleshipPlayer::playerName() const
{
    return *m_name;
}
position BattleshipPlayer::shoot() const
{
    std::cout << "PLAYER SHOOT CALLED\n";
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

        if (std::cin.fail() || !COL_IN_RANGE(row))
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

        if (std::cin.fail() || !ROW_IN_RANGE(col))
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
    // std::cout << "trying to shoot at grid with addr: " << grid << '\n';
    grid->shotAt(pos, hit, initial);
    // std::cout << "shot at grid\n";
}

BattleshipGrid *BattleshipPlayer::getGrid() const
{
    return grid;
}

void BattleshipPlayer::initializeGrid()
{
    // TODO: FIX THIS METHOD BECAUSE THIS DOES NOT WORK
    // UHH COPY THIS SECTION OUT AND MAKE A CLEAN EXAMPLE
    // it's clearly not doing what I'm thinking it should do
    // what I want to do is to swap the grid so that I can
    // assign grid a new pointer on the heap
    // and then delete the old grid from the heap
    // to swap this, I need to keep track of a pointer
    // to the old grid on the heap...

    delete grid;
    grid = new BattleshipGrid();

    // std::cout << "init grid at " << grid << '\n';

    // for now I am just going to leak memory on purpose
    // to make sure that the grid works at least
    // because I might have a deeper error than just a leak
    // XXX: also, the inheritance is not working correctly as of now

    /* BEGIN METHOD CODE
    std::cout << "INIT GRID\n";
    // make a new one and then swap
    BattleshipGrid **tmp = &grid;
    grid = new BattleshipGrid();

    std::cout << "grid addr: " << &grid << '\n';
    std::cout << "*tmp: " << *tmp << '\n';

    if (*tmp != nullptr)
    {
        std::cout << "deleting *tmp with addr: " << *tmp << '\n';
        delete *tmp;
    }
    *tmp = nullptr;

    std::cout << "end grid addr: " << grid << '\n';
    std::cout << "end *tmp: " << *tmp << '\n';

    std::cout << "dereferencing grid in INIT_GRID\n";
    grid->empty(position(1, 1));
    std::cout << "called grid->empty() on (A, 1)\n";
    */
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

    // std::cout << "current addr of grid: " << &grid << '\n';
    // std::cout << "dereferencing grid...\n";

    updateGrid(pos, hit, initial);

    std::cout << NUM_HEADER;
    for (int i = 0; i < GRID_SIZE; i++)
    {
        std::cout << (char)('A' + i) << "  ";
        for (int j = 0; j < GRID_SIZE; j++)
        {
            position gridpos(i, j);
            std::cout << (grid->empty(gridpos) ? SYMBOL_EMPTY : grid->miss(gridpos) ? SYMBOL_MISS
                                                                                    : grid->boatInitial(gridpos))
                      << ' ';
            if (j == GRID_SIZE - 1)
            {
                std::cout << '\n';
            }
        }
    }
    // std::cout << "updated the player successfully\n";
}

BattleshipPlayer::~BattleshipPlayer()
{
    delete grid;
    grid = nullptr;
    // std::cout << "name at addr " << m_name << ": " << *m_name << '\n';

    // std::cout << "name len: " << m_name->size() << '\n';
    // std::cout << "name: " << *m_name << '\n';

    delete m_name;
    m_name = nullptr;
}