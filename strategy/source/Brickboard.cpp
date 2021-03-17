#include "strategy/include/Brickboard.hpp"

Brickboard::Brickboard()
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            m_board[i][j] = BOARD_EMPTY;
        }
    }
}
Brickboard::~Brickboard()
{
}

void Brickboard::placeBoat(std::string boatName, bool vertical, position pos) const
{
    boat b(pos, boatName, vertical);

    if (pos.getRowIndex() < 0 || pos.getColIndex() < 0 || pos.getRowIndex() > 9 || pos.getColIndex() > 9)
    {
        // std::cout << "initial pos out of bounds\n";
        throw std::exception();
    }
    if (vertical)
    {
        if (b.getLength() - 1 + pos.getRowIndex() > 9)
        {
            // std::cout << "vertical boat does not fit\n";
            throw std::exception();
        }

        // check for collision with other boats
        for (int row = pos.getRowIndex(); row < b.getLength() + pos.getRowIndex(); row++)
        {
            // check pos not empty
            if (!m_board[row][pos.getColIndex()])
            {
                // std::cout << "collision\n";
                throw std::exception();
            }
        }
    }
    else
    {
        if (b.getLength() - 1 + pos.getColIndex() > 9)
        {
            // std::cout << "horizonal boat does not fit\n";
            throw std::exception();
        }

        for (int col = pos.getColIndex(); col < b.getLength() + pos.getColIndex(); col++)
        {
            // check pos not empty
            if (!m_board[pos.getRowIndex()][col])
            {
                // std::cout << "collision\n";
                throw std::exception();
            }
        }
    }
}

void Brickboard::restrict(position pos)
{
    m_board[pos.getRowIndex()][pos.getColIndex()] = true;
}

void Brickboard::printMap(std::array<std::array<bool, GRID_SIZE>, GRID_SIZE> map) const
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            std::cout << m_board[i][j] << ' ';
        }
        std::cout << '\n';
    }
}