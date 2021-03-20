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
    boat testBoat(pos, boatName, vertical);

    if (pos.getRowIndex() < 0 || pos.getColIndex() < 0 || pos.getRowIndex() > 9 || pos.getColIndex() > 9)
    {
        // std::cout << "initial pos out of bounds\n";
        throw std::exception();
    }
    if (vertical)
    {
        if (testBoat.getLength() - 1 + pos.getRowIndex() > 9)
        {
            // std::cout << "vertical boat does not fit\n";
            throw std::exception();
        }

        // check for collision with other boats
        for (int row = pos.getRowIndex(); row < testBoat.getLength() + pos.getRowIndex(); row++)
        {
            if (m_board[row][pos.getColIndex()])
            {
                // std::cout << "collision\n";
                throw std::exception();
            }
        }
    }
    else
    {
        if (testBoat.getLength() - 1 + pos.getColIndex() > 9)
        {
            // std::cout << "horizonal boat does not fit\n";
            throw std::exception();
        }

        for (int col = pos.getColIndex(); col < testBoat.getLength() + pos.getColIndex(); col++)
        {
            if (m_board[pos.getRowIndex()][col])
            {
                // std::cout << "collision\n";
                throw std::exception();
            }
        }
    }

    // std::cout << "end placement. no exception thrown\n";
}

void Brickboard::restrict(position pos)
{
    m_board[pos.getRowIndex()][pos.getColIndex()] = BOARD_RESTRICTED;
}

void Brickboard::printMap() const
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