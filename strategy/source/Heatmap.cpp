#include "strategy/include/Heatmap.hpp"

Heatmap::Heatmap(computerplayer *computerplayer) : m_cpuPlayer(computerplayer)
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            m_heatmap[i][j] = 0;
        }
    }
}
Heatmap::~Heatmap()
{
}

void Heatmap::increment(std::vector<position> coords, int weight)
{

    for (position pos : coords)
    {
        // std::cout << "testing at pos: " << pos << '\n';
        // if the grid is not hit at the location in question, increment the heatmap
        if (!m_cpuPlayer->getGrid()->hit(pos))
        {
            // std::cout << "inc heatmap at pos: " << pos << '\n';
            m_heatmap[pos.getRowIndex()][pos.getColIndex()] += weight;
        }
    }

    // std::cout << "done incrementing.\n";
}
void Heatmap::printMap() const
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            std::cout << m_heatmap[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

std::array<std::array<int, GRID_SIZE>, GRID_SIZE> Heatmap::getHeatmap() const
{
    return m_heatmap;
}

position Heatmap::hottestPos() const
{
    position *pos = nullptr;
    int max = -1;
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            int tmp = max;
            max = MAX(max, m_heatmap[i][j]);

            // if the hottest square was changed, find the position of it
            if (tmp != max)
            {
                position hotPos(i, j);
                pos = &hotPos;
            }
        }
    }

    // pos should never be null here since the max is set
    // to -1 at first and the lowest possible value is 0
    return *pos; // TODO: make sure this doesn't do weird scope stuff since it's a pointer
}