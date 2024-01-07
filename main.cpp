#include <iostream>

#include "Day7/include/Day7.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cerr << "Missing input file!\n";
        return EXIT_FAILURE;
    }

    Day7::PartOne(argv[1]);
    Day7::PartTwo(argv[1]);
}
