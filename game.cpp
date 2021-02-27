#include <iostream>

#include "game.hpp"

BattleshipGame::BattleshipGame(BattleshipPlayer player) : m_player(player)
{
    m_ocean = new ocean;
    m_turns = 0;
    m_ocean->placeAllBoats();
    m_player.startGame();
    // m_player.initializeGrid();
}

int BattleshipGame::play()
{
    while (!m_ocean->allSunk() && m_turns <= 100)
    {
        m_turns++;
        position pos = m_player.shoot();
        m_ocean->shootAt(pos);
        m_player.updatePlayer(pos, m_ocean->hit(pos), m_ocean->boatInitial(pos), m_ocean->boatName(pos), m_ocean->sunk(pos), m_ocean->allSunk(), m_turns >= 100, m_turns);
    }
    return m_turns;
}

BattleshipGame::~BattleshipGame()
{
    delete m_ocean;
}