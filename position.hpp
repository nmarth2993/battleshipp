#ifndef POSITION
#define POSITION
#include <iostream>

class position
{
private:
    unsigned char row;
    unsigned char col;

public:
    position(unsigned char row, unsigned char col);
    ~position();
    position(const position &pos);
    bool operator==(const position &pos) const;
    bool operator!=(const position &pos) const;

    // this allows an outside (non-member) function to access private vars
    // !LEARNED! the friend operator is for non-member methods
    friend std::ostream &operator<<(std::ostream &out, const position &pos);

    int getRow();
    int getCol();
};

#endif