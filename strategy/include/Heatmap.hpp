// TODO: rename all files and rename classes, make sure member variables are named m_var

#ifndef HEATMAP
#define HEATMAP

#define MAX(a, b) a > b ? a : b

#include <array>

#include "include/ocean.hpp"
#include "include/computerplayer.hpp"

class Heatmap
{
private:
    std::array<std::array<int, GRID_SIZE>, GRID_SIZE> m_heatmap;
    computerplayer *m_cpuPlayer;

public:
    Heatmap(computerplayer *computerPlayer);
    ~Heatmap();

    void increment(std::vector<position> coords, int weight);
    void printMap() const;
    std::array<std::array<int, GRID_SIZE>, GRID_SIZE> getHeatmap() const;
    position hottestPos() const;
};

#endif