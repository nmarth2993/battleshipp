#define BOUND_ERR_MSG "Out of bounds"
#define OVERLAP_ERR_MSG "Overlap"

#include <time.h>

#include "ocean.hpp"

ocean::ocean()
{
    srand(time(NULL));
    this->fleet.reserve(5);
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            this->grid[i][j] = -1;
        }
    }
}

void ocean::placeBoat(std::string boatName, bool vertical, position pos)
{
    boat boat(pos, boatName, vertical);

    if (pos.getRowIndex() < 0 || pos.getColIndex() < 0 || pos.getRowIndex() > 9 || pos.getColIndex() > 9)
    {
        throw BOUND_ERR_MSG;
    }
    if (vertical)
    {
        if (boat.getLength() - 1 + pos.getRowIndex() > 9)
        {
            throw BOUND_ERR_MSG;
        }
        for (int row = pos.getRowIndex(); row < boat.getLength(); row++)
        {
            if (grid[row][pos.getColIndex()] != -1)
            {
                throw OVERLAP_ERR_MSG;
            }
        }
        for (int row = pos.getRowIndex(); row < boat.getLength(); row++)
        {
            grid[row][pos.getColIndex()] = boatIndex;
        }
    }
    else
    {
        if (boat.getLength() - 1 + pos.getColIndex() > 9)
        {
            throw BOUND_ERR_MSG;
        }
        for (int col = pos.getColIndex(); col < boat.getLength(); col++)
        {
            if (grid[pos.getRowIndex()][col] != -1)
            {
                throw OVERLAP_ERR_MSG;
            }
        }
        for (int col = pos.getColIndex(); col < boat.getLength(); col++)
        {
            grid[pos.getRowIndex()][col] = boatIndex;
        }
    }
    // XXX: may not be able to modify these if the only way I can pass
    // an instance is if the pointer is constant...
    this->fleet.push_back(boat);
    this->boatIndex++;
}

void ocean::placeAllBoats()
{
    bool placed = false;
    for (std::string name : BOAT_NAMES)
    {
        while (!placed)
        {
            try
            {
                placed = true;
                placeBoat(name, (bool)rand() % 2, position(rand() % 9 + 1, rand() % 9 + 1));
            }
            catch (const std::string &errmsg)
            {
                // no error output because this is expected to happen
                // (it will spam the console otherwise)
                // std::cerr << errmsg << '\n';
                placed = false;
            }
        }
        placed = false;
    }
}

bool ocean::sunk(const position pos) const
{
    if (grid[pos.getRowIndex()][pos.getColIndex()] != -1)
    {
        return fleet.at(grid[pos.getRowIndex()][pos.getColIndex()]).sunk();
    }
    return false;
}

bool ocean::allSunk() const
{
    for (int i = 0; i < this->boatIndex; i++)
    {
        if (!fleet.at(i).sunk())
        {
            return false;
        }
    }
    return true;
}

ocean::~ocean()
{
}