// sorry if this file is a little bit all over the place, I'm following my original
// implementation from Java where I used nested classes but I didn't want to do that here
// I'm also on somewhat of a time crunch so I would rather just finish first and then clean it up

#include "strategy/include/computerstrategy.hpp"

computerstrategy::computerstrategy()
{
    // default constructor
    // all of the initialization is done in startGame()

    m_aliveBoats = nullptr;
    m_board = nullptr;
    m_heatmap = nullptr;
}
computerstrategy::~computerstrategy()
{
    delete m_aliveBoats;
    m_aliveBoats = nullptr;

    delete m_board;
    m_board = nullptr;

    delete m_heatmap;
    m_heatmap = nullptr;
}

void computerstrategy::initAliveBoats()
{
    m_aliveBoats = new std::vector<std::string>;
    // std::cout << "alloc'd new vector at " << m_aliveBoats << '\n';
    for (int i = 0; i < 5; i++)
    {
        // std::cout << "copying index " << i << " with name \"" << BOAT_NAMES[i] << "\"\n";
        // copy the boat names into strings
        m_aliveBoats->push_back(std::string(BOAT_NAMES[i]));
    }
}

int computerstrategy::boatSize(std::string boatName) const
{
    if (!boatName.compare(BOAT_NAMES[CRUISER_INDEX]))
    {
        return 3;
    }
    else
    {
        for (size_t i = 0; i < sizeof(BOAT_NAMES) / sizeof(std::string) - 1; i++)
        {
            if (!boatName.compare(BOAT_NAMES[i]))
            {
                return i + 2;
            }
        }
    }

    // return -1 on fail
    return -1;
}

std::vector<position> computerstrategy::sunkDisplacement(position pos, std::string boatName) const
{
    std::vector<position> sunkPositions;

    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if (boatName.at(0) == getGrid()->boatInitial((position(i, j))))
            {
                sunkPositions.push_back(position(i, j));
            }
        }
    }

    return sunkPositions;
}

int computerstrategy::hitIntersection(position pos, std::string name, bool vertical) const
{
    // FIXME: THIS METHOD TAKES IN A BOAT OBJECT SO IT WILL FREE IT AT THE END.
    // IT SEEMS THERE IS A DOUBLE FREE AT THE END. THIS COULD ALSO BE CAUSED BY
    // A PREVIOUS METHOD INCORRECTLY CALLING delete ON THE BOAT

    boat b(pos, name, vertical);

    int count = 0;

    // std::cout << "boat " << b.getName() << " with length " << b.getLength() << '\n';

    for (int i = 0; i < b.getLength(); i++)
    {
        if (b.isVertical())
        {
            // std::cout << "vertical boat\n";
            if (getGrid()->hit(position(b.getPos().getRowIndex() + i, b.getPos().getColIndex())))
            {
                count++;
            }
        }
        else
        {

            // std::cout << "horizontal boat\n";
            if (getGrid()->hit(position(b.getPos().getRowIndex(), b.getPos().getColIndex() + i)))
            {
                count++;
            }
        }
    }

    // std::cout << "num intersections: " << count << '\n';

    return count;
}

std::vector<position> computerstrategy::displacement(position pos, std::string name, bool vertical) const
{
    boat b(pos, name, vertical);

    std::vector<position> positions;
    for (int i = 0; i < b.getLength(); i++)
    {
        if (b.isVertical())
        {
            positions.emplace_back(position(b.getPos().getRowIndex() + i, b.getPos().getColIndex()));
            // positions.push_back(position(b.getPos().getRowIndex() + i, b.getPos().getColIndex()));
        }
        else
        {
            positions.emplace_back(position(b.getPos().getRowIndex(), b.getPos().getColIndex() + i));
            // positions.push_back(position(b.getPos().getRowIndex(), b.getPos().getColIndex() + i));
        }
    }

    return positions;
}

std::string computerstrategy::playerName() const
{
    return "CPU Strategy";
}
std::string computerstrategy::author() const
{
    return "Nicholas Marthinuss";
}

void computerstrategy::startGame()
{
    initAliveBoats();
    m_board = new Brickboard();
    computerplayer::startGame();
}

void computerstrategy::genHeatmap()
{
    delete m_heatmap;
    // TODO: perhaps have a 'clear' method that zeros all positions instead of deallocating and reallocating?
    m_heatmap = new Heatmap(this);
    for (std::string name : *m_aliveBoats)
    {
        bool vertical = true;
        for (int direction = 0; direction < 2; direction++)
        {
            for (int i = 0; i < GRID_SIZE; i++)
            {
                for (int j = 0; j < GRID_SIZE; j++)
                {

                    // boat b(position(i, j), name, vertical);
                    boat b(position(i, j), name, vertical);
                    try
                    {
                        // std::cout << "made boat at addr " << b << '\n';
                        // m_board->placeBoat(b.getName(), b.isVertical(), b.getPos());
                        m_board->placeBoat(b.getName(), b.isVertical(), b.getPos());

                        // m_heatmap->increment(displacement(b), hitIntersection(b) * WEIGHT + 1);

                        // so passing the object in directly into displacement()
                        // or hitIntersection() does something weird and causes a double
                        // free when either method frees the object and then the other
                        // method tries to free the same object again
                        // I thought c++ was pass-by-value? (unless explicitly stated...)

                        // I do not see a problem in my code so for now I will remain confused and
                        // pass in the required information to make a new boat locally scoped on each method

                        std::vector<position> displacedPositions = displacement(b.getPos(), b.getName(), b.isVertical());
                        // std::vector<position> displacedPositions = {position(0, 0), position(1, 0)};

                        // FIXME: calling hitIntersection causes a double free?????
                        int numIntersections = hitIntersection(b.getPos(), b.getName(), b.isVertical());
                        // int numIntersections = 0;

                        // std::cout << "displace and intersect found. incrementing...\n";

                        m_heatmap->increment(displacedPositions, numIntersections * WEIGHT + 1);

                        // m_heatmap->increment(displacement(*b), hitIntersection(*b) * WEIGHT + 1);

                        // std::cout << "after inc\n";
                    }
                    catch (const std::exception &e)
                    {
                        // std::cout << "not incrementing heatmap\n";
                        // do nothing here, the heatmap is not incremented
                    }
                }
            }
            vertical = false;
        }
    }
}

position computerstrategy::shoot()
{
    genHeatmap();

    std::cout << "---heatmap---\n";
    m_heatmap->printMap();
    std::cout << "-------------\n";

    std::cout << "---board---\n";
    m_board->printMap();
    std::cout << "-----------\n";

    for (std::string boatName : *m_aliveBoats)
    {
        std::cout << "alive boat: " << boatName << '\n';
    }

    std::cout << "chose " << m_heatmap->hottestPos() << '\n';

    return m_heatmap->hottestPos();
}

void computerstrategy::updatePlayer(position pos, bool hit, char initial, std::string boatName, bool sunk, bool gameOver, bool tooManyTurns, int turns)
{
    computerplayer::updatePlayer(pos, hit, initial, boatName, sunk, gameOver, tooManyTurns, turns);

    BattleshipPlayer::updatePlayer(pos, hit, initial, boatName, sunk, gameOver, tooManyTurns, turns);

    // std::cout << "addr of m_board: " << m_board << '\n';
    // std::cout << "addr of m_aliveBoats: " << m_aliveBoats << '\n';

    // std::cout << "addr of boatName: " << &boatName << '\n';
    // std::cout << "boatName: " << boatName << '\n';

    if (!hit)
    {
        m_board->restrict(pos);
        // std::cout << "restricting " << pos << '\n';
    }

    if (sunk)
    {

        // m_aliveBoats->erase(m_aliveBoats->begin() + offset);

        // remove the sunk boat from consideration in the heatmap
        auto it = std::find(m_aliveBoats->begin(), m_aliveBoats->end(), boatName);
        if (it != m_aliveBoats->end())
        {
            m_aliveBoats->erase(it);
        }

        // remove the sunk positions from available spaces
        for (position sunkPos : sunkDisplacement(pos, boatName))
        {
            m_board->restrict(sunkPos);
        }
    }
}