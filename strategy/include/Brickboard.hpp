// yes this class is called brickboard, no it doesn't really make sense but it makes
// sense to me and this is what it was named in my original implementation
// and when I read brickboard I think of someone moving a brick on a concrete
// surface to block using that square and the sound of a brick being put down
// is enough for it to make sense and idk what else I would call this so yes

#ifndef BRICKBOARD
#define BRICKBOARD

#include <array>
#include <string>

#include "include/ocean.hpp"
#include "include/position.hpp"

#define BOARD_EMPTY false
#define BOARD_RESTRICTED true

class Brickboard
{
private:
    std::array<std::array<bool, GRID_SIZE>, GRID_SIZE> m_board;

public:
    Brickboard();
    ~Brickboard();

    void placeBoat(std::string boatName, bool vertical, position pos) const;
    void restrict(position pos);
    void printMap() const;
};

#endif