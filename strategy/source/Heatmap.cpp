#include "strategy/include/Heatmap.hpp"

Heatmap::Heatmap()
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

void Heatmap::increment(int *coords[], int weight)
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE - 1; j++) // I don't know why this only iterates to the i-1th element but that's how I did it before and I just wanna get this working first
        {
            if (!m_cpuPlayer->getGrid()->hit(position(coords[i][j], coords[i][j + 1])))
            {
                m_heatmap[coords[i][j]][coords[i][j + 1]] += weight;
            }
        }
    }
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