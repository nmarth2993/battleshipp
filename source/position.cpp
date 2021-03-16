#include <iostream>

#include "../include/position.hpp"

position::position(int row, int col) : row(row), col(col)
{
}

// !LEARNED!
// this one is just a google search away but this is important to know
// as of C++11, this is how you pass through other constructors
position::position(char row, int col) : position((int)row - 'A', col - 1)
{
}

position::position(const position &pos) : row(pos.row), col(pos.col)
{
}

// !LEARNED! the const identifier after the method header
// means that the instance is const (will not be changed in the method)
bool position::operator==(const position &pos) const
{
    return pos.col == col && pos.row == row;
}

bool position::operator==(const position *pos) const
{
    return this->col == pos->col && this->row == pos->row;
    // return *this == *pos;
}

bool position::operator!=(const position &pos) const
{
    return !position::operator==(pos);
}

// overloading injection operator should not be a class member
// so don't use class::operator<<, because it is a global function
std::ostream &operator<<(std::ostream &out, const position &pos)
{
    out << pos.getRow() << "-" << pos.getCol();
    return out;
}

char position::getRow() const
{
    return (char)(row + 'A');
}

int position::getCol() const
{
    return (int)col + 1;
}

int position::getRowIndex() const
{
    return (int)row;
}

int position::getColIndex() const
{
    return (int)col;
}

/*
const position *position::operator*() const
{
    const position *ptr = this;
    return ptr;
}
*/

position::~position()
{
}

// int main()
// {
//     position pos(1, 1);
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
//     std::cout << "row: " << pos.getRow() << std::endl;

//     std::cout << "colIndex: " << another.getColIndex() << std::endl;
//     std::cout << "rowIndex: " << another.getRowIndex() << std::endl;

//     std::cout << pos;
//     // std::cout << another;
//     // std::cout << same;

//     std::cout << std::endl;
//     return 0;
// }