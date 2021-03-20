#include <iostream>

#include "include/game.hpp"

BattleshipGame::BattleshipGame(BattleshipPlayer *player) : m_player(player)
{
    m_ocean = new ocean;
    m_turns = 0;
    m_ocean->placeAllBoats();
    m_player->startGame();

    // std::cout << "(G) new game with player: " << player->playerName() << '\n';
    // std::cout << "(G) type name: " << typeid(*player).name() << '\n';

    // std::cout << "(G) calling player shoot...\n";
    // std::cout << "(G) shoot returned " << player->shoot() << '\n';

    // std::cout << "(p) new game with player: " << m_player->playerName() << '\n';
    // std::cout << "(p) type name: " << typeid(*m_player).name() << '\n';

    // std::cout << "(p) calling player shoot...\n";
    // std::cout << "(p) shoot returned " << m_player->shoot() << '\n';
    // m_player.initializeGrid();
}

int BattleshipGame::play()
{
    while (!m_ocean->allSunk() && m_turns <= 100)
    {
        m_turns++;
        position pos = m_player->shoot();
        // std::cout << "shot at " << pos << '\n';
        m_ocean->shootAt(pos);
        m_player->updatePlayer(pos, m_ocean->hit(pos), m_ocean->boatInitial(pos), m_ocean->boatName(pos), m_ocean->sunk(pos), m_ocean->allSunk(), m_turns >= 100, m_turns);
    }
    return m_turns;
}

BattleshipGame::~BattleshipGame()
{
    delete m_ocean;
    m_ocean = nullptr;
}