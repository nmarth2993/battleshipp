#include <iostream>

#include "position.hpp"

position::position(unsigned char row, unsigned char col) : row(row), col(col)
{
}

position::position(const position &pos)
{
    col = pos.col;
    row = pos.row;
}

// !LEARNED! the const identifier after the method header
// means that the instance is const
bool position::operator==(const position &pos) const
{
    return pos.col == col && pos.row == row;
}

bool position::operator!=(const position &pos) const
{
    return !position::operator==(pos);
}

// overloading injection operator should not be a class member
// so don't use class::operator<<, because it is a global function
std::ostream &operator<<(std::ostream &out, const position &pos)
{
    out << "(" << (int)pos.row << ", " << (int)pos.col << ")";
    return out;
}

int position::getRow()
{
    return (int)row;
}

int position::getCol()
{
    return (int)col;
}

position::~position()
{
}

// int main()
// {
//     position pos(1, 2);
//     position another(1, 3);
//     position same(1, 3);

//     if (same == another)
//     {
//         std::cout << "wow, I did something" << std::endl;
//     }
//     if (same != pos)
//     {
//         std::cout << "worked again" << std::endl;
//     }

//     std::cout << "col: " << pos.getCol() << std::endl;

//     std::cout << pos;

//     std::cout << std::endl;
//     return 0;
// }