#include <iostream>
#include "grid.hpp"

BattleshipGrid::BattleshipGrid()
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            this->grid[i][j] = SYMBOL_EMPTY;
        }
    }
}

void BattleshipGrid::shotAt(position pos, bool hit, char initial)
{
    if (!hit)
    {
        grid[pos.getRowIndex()][pos.getColIndex()] = SYMBOL_MISS;
    }
    else
    {
        grid[pos.getRowIndex()][pos.getColIndex()] = initial;
    }
}

bool BattleshipGrid::hit(position pos) const
{
    return grid[pos.getRowIndex()][pos.getColIndex()] != SYMBOL_EMPTY && grid[pos.getRowIndex()][pos.getColIndex()] != SYMBOL_MISS;
}

bool BattleshipGrid::miss(position pos) const
{
    return grid[pos.getRowIndex()][pos.getColIndex()] == SYMBOL_MISS;
}

bool BattleshipGrid::empty(position pos) const
{
    return grid[pos.getRowIndex()][pos.getColIndex()] == SYMBOL_EMPTY;
}

// return the boat's initial at pos
// assuming that this method will only be called on a position
// that has a boat and has been hit
char BattleshipGrid::boatInitial(position pos) const
{
    if (hit(pos))
    {
        return grid[pos.getRowIndex()][pos.getColIndex()];
    }
    return ' ';
}

BattleshipGrid::~BattleshipGrid()
{
    delete[] grid;
}