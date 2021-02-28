#include <iostream>

/*
int main(int argc, const char *argv[])
{
    int *ptr = nullptr;
    int **tmp = &ptr;

    // ptr = new int(9);

    if (*tmp == nullptr)
    {
        std::cout << "null\n";
    }
    else
    {
        std::cout << "temp not pointing to null\n";
    }

    if (*tmp != nullptr)
    {
        std::cout << "ptr: " << *ptr << " at addr: " << ptr << '\n';
    }

    std::cout << "tmp: " << *tmp << " at addr: " << tmp << '\n';

    delete *tmp;
    std::cout << "deleted tmp\n";

    return 0;
}
*/

class testclass
{
private:
public:
    testclass();
    ~testclass();
};

testclass::testclass()
{
}

testclass::~testclass()
{
}

int main(int argc, char const *argv[])
{
    testclass *grid = nullptr;
    testclass **tmp = &grid;

    std::cout << "grid addr: " << grid << '\n';
    std::cout << "tmp ptr: " << *tmp << '\n';
    std::cout << "tmp addr: " << tmp << '\n';

    grid = new testclass();

    std::cout << "grid addr: " << grid << '\n';
    std::cout << "tmp ptr: " << *tmp << '\n';
    std::cout << "tmp addr: " << tmp << '\n';

    if (*tmp != nullptr)
    {
        delete *tmp;
    }
    *tmp = nullptr;
    return 0;
}
