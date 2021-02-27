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
    std::vector<position *> *displacement;

    bool hasPos(const position pos) const;
    int hasPosIndex(const position pos) const;

public:
    boat(position pos, std::string name, bool vertical);

    friend std::ostream &operator<<(std::ostream &out, const boat &boat);

    int getLength() const;
    char abbrev() const;
    position getPos() const;
    std::string getName() const;
    bool isVertical() const;

    bool onBoat(const position pos) const;

    bool isHit(const position pos) const;
    void hit(const position pos);
    bool sunk() const;

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

#define CRUISER_INDEX 4

static const std::string BOAT_NAMES[] = {
    "Destroyer",
    "Submarine",
    "Battleship",
    "Aircraft Carrier",
    "Cruiser",
};

#endif