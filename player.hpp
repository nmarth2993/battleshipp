#ifndef BATTLESHIP_PLAYER
#define BATTLESHIP_PLAYER

#include "grid.hpp"

class BattleshipPlayer
{
private:
    BattleshipGrid *grid; // to avoid constructing object
    std::string *m_name;

public:
    BattleshipPlayer();

    void startGame();
    std::string playerName() const;
    position shoot() const;
    void updateGrid(position pos, bool hit, char initial);
    BattleshipGrid getGrid() const;
    void initializeGrid();
    void updatePlayer(position pos, bool hit, char initial, std::string boatName, bool sunk, bool gameOver, bool tooManyTurns, int turns);

    ~BattleshipPlayer();
};

#endif