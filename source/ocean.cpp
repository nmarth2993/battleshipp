// #define BOUND_ERR_MSG boundexcept
// #define OVERLAP_ERR_MSG overlapexcept

#include <string.h>

#include "../include/ocean.hpp"

// const static std::string sub("Submarine");
// const static boat TEST_BOAT(position(1, 1), sub, true);

// static BoundsException boundexcept;
// static OverlapException overlapexcept;

ocean::ocean()
{
    this->fleet = new std::vector<boat *>;
    // this->fleet->reserve(5);
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            this->grid[i][j] = -1;
        }
    }
    boatIndex = 0;
}

void ocean::placeBoat(std::string boatName, bool vertical, position pos)
{
    // create a temporary boat to test that it can fit first
    boat b(pos, boatName, vertical);
    // std::cout << "place attempt: " << b << '\n';

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

        // if (pos.getRowIndex() >= b.getLength() + pos.getRowIndex())
        // {
        //     std::cout << "rowIndex >= boat length + rowIndex (row index: " << pos.getRowIndex() << ", " << b.getLength() + pos.getRowIndex() << ")\n";
        // }

        // check for collision with other boats
        for (int row = pos.getRowIndex(); row < b.getLength() + pos.getRowIndex(); row++)
        {
            if (grid[row][pos.getColIndex()] != -1)
            {
                // std::cout << "collision\n";
                throw std::exception();
            }
        }

        // if no collision was found, place the boat on the ocean
        for (int row = pos.getRowIndex(); row < b.getLength() + pos.getRowIndex(); row++)
        {
            // std::cout << "setting index "
            //           << "(" << row << ", " << pos.getColIndex() << ")\n";
            // std::cout << "to index: " << boatIndex << '\n';

            grid[row][pos.getColIndex()] = boatIndex;
        }
    }
    else
    {
        if (b.getLength() - 1 + pos.getColIndex() > 9)
        {
            // std::cout << "horizonal boat does not fit\n";
            throw std::exception();
        }

        // if (pos.getColIndex() >= b.getLength())
        // {
        // std::cout << "colIndex >= boat length (col index: " << pos.getColIndex() << ", " << b.getLength() << ")\n";
        // }

        for (int col = pos.getColIndex(); col < b.getLength() + pos.getColIndex(); col++)
        {
            if (grid[pos.getRowIndex()][col] != -1)
            {
                // std::cout << "collision\n";
                throw std::exception();
            }
        }
        for (int col = pos.getColIndex(); col < b.getLength() + pos.getColIndex(); col++)
        {
            // std::cout << "setting index "
            // << "(" << pos.getRowIndex() << ", " << col << ")\n";
            // std::cout << "to index: " << boatIndex << '\n';

            grid[pos.getRowIndex()][col] = boatIndex;
        }
    }
    // XXX: may not be able to modify these if the only way I can pass
    // an instance is if the pointer is constant...

    // boat *newboat = new boat(pos, boatName, vertical);

    // !LEARNED!
    // This one took me a while, but at least I learned some important things about the inner workings
    // of C++. so... dereferencing a new pointer makes a copy so that always causes a memory leak, so don't do that...
    // also, vectors allocate their own memory so I do not need to handle doing that meaning I don't have to
    // allocate on the heap :)))))))

    // once we know that we do actually want the boat, we make a real one that
    // doesn't get deallocated once we drop out of scope
    this->fleet->emplace_back(new boat(pos, boatName, vertical));
    // this->fleet->push_back(TEST_BOAT);

    // !LEARNED! when std::vectors go out of scope, it calls
    // destructors for each object it contains

    // for (boat b : fleet)
    // {
    //     std::cout << "boat: " << b << '\n';
    // }

    this->boatIndex++;

    // I think I see what's happening here...
    // I'm adding a STACK variable to a vector,
    // and then I go out of scope so the variable is destroyed
    // when the program ends, it tries to dealloc the vector
    // and its components, but the components have already been kill
}

void ocean::placeAllBoats()
{
    bool placed = false;
    for (std::string name : BOAT_NAMES)
    {
        // std::cout << "trying to place: " << name << std::endl;
        while (!placed)
        {
            try
            {
                placed = true;
                placeBoat(name, (bool)rand() % 2, position(rand() % 9 + 1, rand() % 9 + 1));
            }
            catch (const std::exception &errmsg)
            {
                // no error output because exceptions are expected to happen
                // (it will spam the console otherwise)
                // std::cerr << errmsg << '\n';
                placed = false;
            }
        }
        // std::cout << "placed boat\n";

        placed = false;
    }
}

bool ocean::sunk(const position pos) const
{
    if (grid[pos.getRowIndex()][pos.getColIndex()] != -1)
    {
        return fleet->at(grid[pos.getRowIndex()][pos.getColIndex()])->sunk();
    }
    return false;
}

bool ocean::allSunk() const
{
    for (boat *b : *this->fleet)
    {
        // std::cout << *b << std::endl;
        if (!b->sunk())
        {
            return false;
        }
    }
    return true;

    /*
    for (int i = 0; i < this->boatIndex; i++)
    {
        if (!fleet->at(i)->sunk())
        {
            return false;
        }
    }
    return true;
    */
}

char ocean::boatInitial(const position pos) const
{
    if (grid[pos.getRowIndex()][pos.getColIndex()] != -1)
    {
        return fleet->at(grid[pos.getRowIndex()][pos.getColIndex()])->abbrev();
    }
    return ' ';
}
std::string ocean::boatName(const position pos) const
{
    if (grid[pos.getRowIndex()][pos.getColIndex()] != -1)
    {
        return fleet->at(grid[pos.getRowIndex()][pos.getColIndex()])->getName();
    }
    return "";
}

bool ocean::hit(const position pos)
{
    if (grid[pos.getRowIndex()][pos.getColIndex()] != -1)
    {
        return fleet->at(grid[pos.getRowIndex()][pos.getColIndex()])->isHit(pos);
    }
    return false;
}

void ocean::shootAt(const position pos)
{
    if (grid[pos.getRowIndex()][pos.getColIndex()] != -1)
    {
        // std::cout << "boat found at " << pos << '\n';
        fleet->at(grid[pos.getRowIndex()][pos.getColIndex()])->hit(pos);
    }
}

ocean::~ocean()
{
    // clear calls all object destructors
    // but I believe I have to do this instead
    // because the objects themselves were allocated with
    // new, not just their member fields and such

    // ??????????????????????
    // i am confusion

    /*
    for (int i = 0; i < (int)this->fleet->size(); i++)
    {
        std::cout << "index " << i << ": " << this->fleet->at(i) << '\n';
    }
    std::cout << std::endl;
    for (int i = 0; i < (int)this->fleet->size(); i++)
    {
        std::cout << "addr: " << &this->fleet->at(i) << '\n';
    }
    std::cout << std::endl;
    */

    // delete each boat
    // what we are doing here is going item by item for every boat
    // in the vector and deleting the address of the object at index i
    /*
    for (int i = 0; i < (int)this->fleet->size(); i++)
    {
        boat *ptr;
        ptr = &this->fleet->at(i);
        std::cout << "current pointer: " << ptr << '\n';
        std::cout << "attempt to dereference: " << *ptr << '\n';
        delete ptr;
        ptr = nullptr;
    }
    */
    // okay so this method calls the destructor for each object and then deallocates
    // the memory... pretty sure this means that it also deletes the vector itself
    // which would explain why I couldn't do fleet->clear() and then delete this->fleet

    // this->fleet->clear();

    // this->fleet->clear(); // this just calls the boat destructors
    // delete this->fleet;
    // delete this->fleet;
    // delete this->fleet;
    // this->fleet = nullptr;
    // std::cout << "dtor called, fleet: " << &this->fleet << '\n';

    // delete this->fleet;

    // std::cout << "destroying ocean" << '\n';

    // std::cout << "end: " << *(this->fleet->end().base()) << '\n';
    // std::cout << "end addr: " << &this->fleet->end().base() << '\n';

    // this->fleet->clear(); // this should call the destructor for every position class in the vector
    // not calling vector::clear() because it now holds pointers

    for (boat *b : *this->fleet)
    {
        delete b;
        b = nullptr;
    }

    delete this->fleet;
    this->fleet = nullptr;
    // std::cout << "deleted pointer\n";
    // fleet = nullptr;
    // std::cout << "destroyed ocean" << '\n';
}

// https://stackoverflow.com/questions/16527829/is-it-considered-good-style-to-dereference-new-pointer