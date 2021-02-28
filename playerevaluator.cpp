#include "playerevaluator.hpp"
#include "game.hpp"

#define min(a, b) (a < b ? a : b)
#define max(a, b) (a > b ? a : b)

PlayerEvaluator::PlayerEvaluator(computerplayer player, int runs)
{
    for (int i = 0; i < runs; i++)
    {
        turns = BattleshipGame(player).play();
        m_sumTurns += turns;
        m_minTurns = min(m_minTurns, turns);
        m_maxTurns = max(m_maxTurns, turns);
    }
    m_avgTurns = (float)m_sumTurns / (float)runs;
}

int PlayerEvaluator::maxTurns() const
{
    return m_maxTurns;
}

int PlayerEvaluator::minTurns() const
{
    return m_minTurns;
}

float PlayerEvaluator::averageTurns() const
{
    return m_avgTurns;
}

PlayerEvaluator::~PlayerEvaluator()
{
}