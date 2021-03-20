#ifndef CPU_STRATEGY
#define CPU_STRATEGY

#include <vector>
#include <algorithm>
#include <string>

#include "include/computerplayer.hpp"

#include "strategy/include/Heatmap.hpp"
#include "strategy/include/Brickboard.hpp"

#define WEIGHT 5

class computerstrategy : public computerplayer
{
private:
    std::vector<std::string> *m_aliveBoats;
    Brickboard *m_board;
    Heatmap *m_heatmap;

    void initAliveBoats();
    std::vector<position> sunkDisplacement(position pos, std::string boatName) const;
    int hitIntersection(position pos, std::string name, bool vertical) const;
    std::vector<position> displacement(position pos, std::string name, bool vertical) const;

    int boatSize(std::string boatName) const;

public:
    computerstrategy();
    ~computerstrategy();

    std::string playerName() const;
    std::string author() const;

    void startGame();
    position shoot();
    void updatePlayer(position pos, bool hit, char initial, std::string boatName, bool sunk, bool gameOver, bool tooManyTurns, int turns);

    void genHeatmap();
};

#endif