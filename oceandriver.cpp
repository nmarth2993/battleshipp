#include <iostream>

#include "ocean.hpp"

int main(int argc, char const *argv[])
{
    ocean myOcean;

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

    return 0;
}