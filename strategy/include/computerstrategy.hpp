#ifndef CPU_STRATEGY
#define CPU_STRATEGY

#include <vector>
#include <string>

#include "include/computerplayer.hpp"

#include "strategy/include/Heatmap.hpp"
#include "strategy/include/Brickboard.hpp"

class computerstrategy : public computerplayer
{
private:
    std::vector<std::string> *m_aliveBoats;
    Brickboard *m_board;
    Heatmap *m_map;

    void initAliveBoats();
    position *sunkDisplacement(position pos, std::string boatName);
    int boatSize(std::string boatName);

public:
    computerstrategy();
    ~computerstrategy();

    std::string playerName() const;
    std::string author() const;

    void startGame();
    position shoot() const;
    void updatePlayer(position pos, bool hit, char initial, std::string boatName, bool sunk, bool gameOver, bool tooManyTurns, int turns);
};

#endif