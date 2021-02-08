#ifndef BOAT
#define BOAT

#include <iostream>
#include <vector>

#include "position.hpp"

class boat
{
private:
    position pos;
    std::string name;
    bool vertical;

    bool *hits;
    std::vector<position> *displacement;

public:
    boat(position pos, std::string name, bool vertical);

    friend std::ostream &operator<<(std::ostream &out, const boat &boat);

    int getLength() const;
    char abbrev() const;
    std::string getName() const;
    position getPos() const;
    std::string getName() const;
    bool isVertical() const;

    bool hasPos(const position pos) const;
    bool hasPosIndex(const position pos) const;

    ~boat();
};

enum BOAT_LENGTHS
{
    DESTROYER = 2,
    SUBMARINE,
    BATTLESHIP,
    CARRIER,
    CRUISER = 3
};

static const std::string BOAT_NAMES[] = {
    "Destroyer",
    "Submarine",
    "Battleship",
    "Carrier",
    "Cruiser",
};

#endif