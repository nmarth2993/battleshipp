#ifndef OCEAN
#define OCEAN

#define GRID_SIZE 10

#include <vector>
#include <exception>
#include "boat.hpp"

class ocean
{
private:
    std::vector<boat> fleet;
    int grid[10][10];
    int boatIndex = 0;

public:
    ocean();

    void placeBoat(const std::string boatName, const bool vertical, const position pos);
    void placeAllBoats();

    void shootAt(const position pos);
    bool hit(const position pos);

    char boatInitial(const position pos) const;
    std::string boatName(const position pos) const;

    bool sunk(const position pos) const;
    bool allSunk() const;

    ~ocean();
};

/*
class BoundsException : public std::exception
{
private:
    // data
public:
    BoundsException();

    char const *what() const throw();

    ~BoundsException();
};

BoundsException::BoundsException()
{
}

char const *BoundsException::what() const throw()
{
    return "Out of bounds exception";
}

BoundsException::~BoundsException()
{
}

class OverlapException
{
private:
    // data
public:
    OverlapException();

    char const *what() const throw();

    ~OverlapException();
};

OverlapException::OverlapException()
{
}

char const *OverlapException::what() const throw()
{
    return "Overlap exception";
}

OverlapException::~OverlapException()
{
}
*/
#endif