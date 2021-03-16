#include <vector>
#include <string>

#include "computerplayer.hpp"

class computerstrategy : public computerplayer
{
private:
    std::vector<std::string> aliveBoats;

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