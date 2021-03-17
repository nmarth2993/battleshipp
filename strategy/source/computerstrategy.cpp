#include "strategy/include/computerstrategy.hpp"

computerstrategy::computerstrategy()
{
    // default constructor
    // all of the initialization is done in startGame()
}
computerstrategy::~computerstrategy()
{
    delete m_aliveBoats;
    m_aliveBoats = nullptr;

    delete m_board;
    m_board = nullptr;

    delete m_map;
    m_map = nullptr;
}

std::string computerstrategy::playerName() const
{
}
std::string computerstrategy::author() const
{
}

void computerstrategy::startGame()
{
}

position computerstrategy::shoot() const
{
}

void computerstrategy::updatePlayer(position pos, bool hit, char initial, std::string boatName, bool sunk, bool gameOver, bool tooManyTurns, int turns)
{
}