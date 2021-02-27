#ifndef POSITION
#define POSITION
#include <iostream>

class position
{
private:
    int row;
    int col;

public:
    position(int row, int col);
    ~position();
    position(const position &pos);
    bool operator==(const position &pos) const;
    bool operator==(const position *pos) const;
    bool operator!=(const position &pos) const;
    // const position *operator*() const;

    // this allows an outside (non-member) function to access private vars
    // !LEARNED! the friend operator is for non-member methods
    friend std::ostream &operator<<(std::ostream &out, const position &pos);

    char getRow() const;
    int getCol() const;

    int getRowIndex() const;
    int getColIndex() const;
};

#endif