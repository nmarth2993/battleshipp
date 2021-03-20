#ifndef PLAYER_EVALUATOR
#define PLAYER_EVALUATOR

#include "computerplayer.hpp"

class PlayerEvaluator
{
private:
    int m_sumTurns = 0;
    int m_maxTurns = 0;
    int m_minTurns = 100;
    float m_avgTurns;
    int turns;

public:
    PlayerEvaluator(computerplayer *player, int runs);

    int maxTurns() const;
    int minTurns() const;
    float averageTurns() const;

    ~PlayerEvaluator();
};

#endif