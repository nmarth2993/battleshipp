#ifndef BATTLESHIP_PLAYER
#define BATTLESHIP_PLAYER

#include "grid.hpp"

class BattleshipPlayer
{
private:
    std::string *m_name;

protected:
    BattleshipGrid *grid; // to avoid constructing object

public:
    BattleshipPlayer();

    virtual void startGame();
    virtual std::string playerName() const;
    virtual position shoot() const;
    void updateGrid(position pos, bool hit, char initial);
    BattleshipGrid *getGrid() const;
    void initializeGrid();
    virtual void updatePlayer(position pos, bool hit, char initial, std::string boatName, bool sunk, bool gameOver, bool tooManyTurns, int turns);

    virtual ~BattleshipPlayer();
};

#endif