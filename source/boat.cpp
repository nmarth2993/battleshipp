#include <iostream>
#include <vector>

#include "../include/boat.hpp"

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
    // std::cout << "len: " << length << std::endl;
    if (length == -1)
    {
        std::cerr << "ships cannot have negative length" << std::endl;
        exit(-1);
    }

    // make arrays to keep track of hits and positions of ship
    // !LEARNED! don't forget the this-> to operate on the instance
    // instead of causing a leak for no reason lol

    // std::cout << "length: " << length << '\n';
    this->hits = new bool[length];

    for (int i = 0; i < length; i++)
    {
        this->hits[i] = false;
    }

    // position squares = new position[length];

    // allocate this on heap so that it stays until the boat is destroyed (both meanings)
    // std::vector<position> *boatPositions = new std::vector<position>;
    // this->displacement = boatPositions;
    this->displacement = new std::vector<position *>;

    // build displacement array
    for (int i = 0; i < length; i++)
    {
        // std::cout << "pushed x: " << this->pos.getRowIndex() + 1 + (this->isVertical() ? i : 0) << " pushed y: " << this->pos.getColIndex() + 1 + (this->isVertical() ? 0 : i) << std::endl;
        displacement->emplace_back(new position(this->pos.getRowIndex() + (this->isVertical() ? i : 0), this->pos.getColIndex() + (this->isVertical() ? 0 : i)));
    }
}

int boat::getLength() const
{
    // !LEARNED! arrays are 0-indexed :^)
    // also this is why we don't hard-code things
    if (!this->name.compare(BOAT_NAMES[CRUISER_INDEX]))
    {
        // std::cout << "cruiser" << std::endl;
        return 3;
    }
    else
    {
        for (size_t i = 0; i < sizeof(BOAT_NAMES) / sizeof(std::string) - 1; i++)
        {
            if (!this->name.compare(BOAT_NAMES[i]))
            {
                // other than the last one, the indices will offset +2
                // std::cout << "match at index " << i << ", len: " << i + 2 << std::endl;
                return i + 2;
            }
        }
    }
    // std::cerr << "failed to match length to name: " << this->name << std::endl;

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

// returns a boolean of whether or not the ship has the given position
bool boat::hasPos(const position pos) const
{
    return hasPosIndex(pos) != -1;
}

// returns the index of the matching positition, -1 if no match found
int boat::hasPosIndex(const position pos) const
{

    // std::cout << "vector contents:\n";
    // for (position *p : *this->displacement)
    // {
    // std::cout << *p << '\n';
    // }

    for (std::vector<position *>::size_type i = 0; i != this->displacement->size(); i++)
    {
        // std::cout << "check: " << pos << " == " << *this->displacement->at(i) << " " << (pos == *this->displacement->at(i)) << '\n';
        if (pos == this->displacement->at(i))
        {
            // std::cout << "MATCHED POSITION\n";
            return i;
        }
    }
    return -1;
}

// return strue if `pos` is on the boat
bool boat::onBoat(const position pos) const
{
    return this->hasPos(pos);
}

// returns true if `pos` is hit, else false
bool boat::isHit(const position pos) const
{
    if (!this->hasPos(pos))
    {
        return false;
    }
    else
    {
        // this is not the *best* structure but I
        // am following years-old code from myself and
        // I'll just roll with it
        return this->hits[hasPosIndex(pos)];
    }
}

// records a hit on the boat if `pos` matches
// any position on the boat's displacement
void boat::hit(const position pos)
{
    if (this->hasPos(pos))
    {
        // std::cout << "has pos " << pos << '\n';
        this->hits[hasPosIndex(pos)] = true;
    }
}

// returns true if the boat is sunk, else false
// the boat is sunk when all of the positons have been hit
bool boat::sunk() const
{
    // std::cout << "checking sunk() with length " << this->getLength() << '\n';
    // std::cout << "hits[0]: " << this->hits[0] << '\n';
    for (int i = 0; i < this->getLength(); i++)
    {
        if (!this->hits[i])
        {
            // std::cout << "no hit at index " << i << '\n';
            return false;
        }
    }
    return true;
}

// boat destructor
boat::~boat()
{
    // std::cout << "destroying boat " << *this << std::endl;
    delete[] hits;
    hits = nullptr;
    // this->displacement->clear(); // this should call the destructor for every position class in the vector
    // not using vector::clear() because the vector now holds pointers

    for (position *p : *this->displacement)
    {
        delete p;
        p = nullptr;
    }

    delete this->displacement;
    displacement = nullptr;
    // std::cout << "destroyed boat" << std::endl;
}

// int main(int argc, const char *argv[])
// {
//     boat b(position{1, 1}, std::string{"Destroyer"}, false);
//     boat c(position{1, 2}, std::string{"Carrier"}, true);

//     std::cout << b << '\n';
//     std::cout << c << '\n';

//     // !LEARNED! I don't need to (should NOT) call these destructors
//     // this will cause a double free. the reason for this is that b and c
//     // were both made on the stack, NOT using the new keyword
//     // this means that once they are out of scope, they will be automatically
//     // deallocated and any deallocation before will cause this second automatic
//     // deallocation to throw a double free error
//     // if I were to have created b and c with new, then I would have to manually
//     // destroy them or else they would be leaked
//     // b.~boat();
//     // c.~boat();

//     return 0;
// }