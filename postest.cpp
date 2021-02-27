#include <iostream>

// #include "position.hpp"

int main(int argc, const char *argv[])
{
    // position pos('A', 1);
    // position pos2('F', 2);
    // position pos3('B', 5);

    // std::cout << "1: " << pos << " 2: " << pos2 << " 3: " << pos3 << '\n';

    char a;
    std::cout << "enter char: ";
    std::cin >> a;

    a &= ~0x20;

    std::cout << "upper: " << a << '\n';

    return 0;
}