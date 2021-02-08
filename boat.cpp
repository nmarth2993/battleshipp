#include <iostream>
#include <vector>

#include "boat.hpp"

boat::boat(position pos, std::string name, bool vertical) : pos(pos), name(name), vertical(vertical)
{
    bool valid = false;

    for (std::string boat_name : BOAT_NAMES)
    {
        if (!name.compare(boat_name))
        {
            valid = true;
            this->name = name;
        }
    }
    if (!valid)
    {
        std::cerr << "you didn't enter a correct boat name (or something else went wrong)" << std::endl;
        exit(-1);
    }

    int length = this->getLength();
    std::cout << "len: " << length << std::endl;

    // make arrays to keep track of hits and positions of ship
    // !LEARNED! don't forget the this-> to operate on the instance
    // instead of causing a leak for no reason lol
    this->hits = new bool[length];

    // position squares = new position[length];

    // allocate this on heap so that it stays until the boat is destroyed (both meanings)
    std::vector<position> *boatPositions = new std::vector<position>;
    this->displacement = boatPositions;

    // build displacement array
    for (int i = 0; i < length; i++)
    {
        std::cout << "pushed x: " << this->pos.getRow() + (this->isVertical() ? i : 0) << " pushed y: " << this->pos.getCol() + (this->isVertical() ? 0 : i) << std::endl;
        boatPositions->push_back(position(this->pos.getRow() + (this->isVertical() ? i : 0), this->pos.getCol() + (this->isVertical() ? 0 : i)));
    }
}

int boat::getLength() const
{
    if (this->name.compare(BOAT_NAMES[5]))
    {
        return 3;
    }
    else
    {
        for (size_t i = 0; i < sizeof(BOAT_NAMES) / sizeof(std::string) - 1; i++)
        {
            if (!this->name.compare(BOAT_NAMES[i]))
            {
                // other than the last one, the indices will offset +2
                return i + 2;
            }
        }
    }

    return -1;
}

std::ostream &operator<<(std::ostream &out, const boat &boat)
{
    out << boat.abbrev() << " (" << boat.getPos().getRow() << ", " << boat.getPos().getCol() << ")";
    // !LEARNED! it is convention to return the ostream so that you can chain operators:
    // a << b << c;
    // the above only works if the ostream "falls through" to the next function call
    return out;
}

position boat::getPos() const
{
    return this->pos;
}

std::string boat::getName() const
{
    return this->name;
}

bool boat::isVertical() const
{
    return this->vertical;
}

char boat::abbrev() const
{
    return this->name.at(0);
}

std::string boat::getName() const
{
    return this->name;
}

bool boat::hasPos(const position pos) const
{
    // iterate over vector
    // std::vector<position>::iterator it = this->displacement->begin(); it != this->displacement->end(); it++
    for (position p : *(this->displacement))
    {
        if (pos == p)
        {
            return true;
        }
    }
    return false;
}

// returns the index of the matching positition, -1 if no match found
bool boat::hasPosIndex(const position pos) const
{
    for (std::vector<position>::size_type i = 0; i != this->displacement->size(); i++)
    {
        if (pos == this->displacement->at(i))
        {
            return i;
        }
    }
    return -1;
}

// boat destructor
boat::~boat()
{
    delete[] this->hits;
    delete this->displacement;
}

int main(int argc, const char *argv[])
{
    boat b(position{1, 1}, std::string{"Destroyer"}, false);
    boat c(position{1, 2}, std::string{"Carrier"}, true);

    std::cout << b << '\n';
    std::cout << c << '\n';

    // !LEARNED! I don't need to (should NOT) call these destructors
    // this will cause a double free. the reason for this is that b and c
    // were both made on the stack, NOT using the new keyword
    // this means that once they are out of scope, they will be automatically
    // deallocated and any deallocation before will cause this second automatic
    // deallocation to throw a double free error
    // if I were to have created b and c with new, then I would have to manually
    // destroy them or else they would be leaked
    // b.~boat();
    // c.~boat();

    return 0;
}