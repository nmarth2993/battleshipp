#include "include/playerevaluator.hpp"
#include "include/game.hpp"

#define min(a, b) (a < b ? a : b)
#define max(a, b) (a > b ? a : b)

PlayerEvaluator::PlayerEvaluator(computerplayer *player, int runs)
{
    BattleshipGame *game;

    // std::cout << "typeid: " << typeid(*player).name() << '\n';

    // std::cout << "name of player: " << player->playerName() << '\n';
    // std::cout << "calling player shoot...\n";
    // std::cout << "player shoot returned: " << player->shoot() << '\n';

    bool halfwayNotif = false;

    for (int i = 0; i < runs; i++)
    {
        game = new BattleshipGame(player);
        turns = game->play();

        // turns = BattleshipGame(&player).play();
        // std::cout << "game " << i + 1 << " finished with " << turns << " turns\n";

        if (!halfwayNotif && i > runs / 2)
        {
            std::cout << "50% completed\n";
            halfwayNotif = true;
        }

        m_sumTurns += turns;
        m_minTurns = min(m_minTurns, turns);
        m_maxTurns = max(m_maxTurns, turns);

        delete game;
        game = nullptr;
    }
    // std::cout << m_sumTurns << '/' << runs << '=' << (float)m_sumTurns / (float)runs;
    m_avgTurns = (float)m_sumTurns / (float)runs;
    std::cout << "avg: " << m_avgTurns << '\n';
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