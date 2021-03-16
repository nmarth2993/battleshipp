#ifndef GRID
#define GRID

#include <string>

#include "position.hpp"
#include "boat.hpp"
#include "ocean.hpp"

#define SYMBOL_EMPTY '.'
#define SYMBOL_MISS '*'

class BattleshipGrid
{
private:
    char (*grid)[GRID_SIZE];

public:
    BattleshipGrid();

    void shotAt(position pos, bool hit, char initial);

    bool hit(position pos) const;
    bool miss(position pos) const;
    bool empty(position pos) const;
    char boatInitial(position pos) const;

    friend std::ostream &operator<<(std::ostream &out, const BattleshipGrid &grid);

    ~BattleshipGrid();
};

#endif