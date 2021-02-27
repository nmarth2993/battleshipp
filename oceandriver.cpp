#include <iostream>

#include "ocean.hpp"

int main(int argc, char const *argv[])
{
    ocean myOcean;

    // ocean *myOcean = new ocean();

    myOcean.placeAllBoats();

    std::cout << "All sunk: " << myOcean.allSunk() << std::endl;

    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            char abbrev = myOcean.boatInitial(position(i, j));
            if (abbrev == ' ')
            {
                std::cout << ". ";
            }
            else
            {
                std::cout << abbrev << " ";
            }
        }
        std::cout << "\n";
    }

    std::cout << "\n\n";

    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            position pos(i, j);
            myOcean.shootAt(pos);
        }
    }

    std::cout << "All sunk: " << myOcean.allSunk() << '\n';

    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            char abbrev = myOcean.boatInitial(position(i, j));
            if (abbrev == ' ')
            {
                std::cout << ". ";
            }
            else
            {
                std::cout << abbrev << " ";
            }
        }
        std::cout << "\n";
    }

    // std::cout << "test" << std::endl;
    // it blows up when auto-deallocating a destroyer that
    // has already been freed... where may I have allocated a new boat?

    return 0;
}