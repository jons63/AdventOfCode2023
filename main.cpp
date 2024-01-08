#include <iostream>

#include "include/Day8.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cerr << "Missing input file!\n";
        return EXIT_FAILURE;
    }

    //Day8::PartOne(argv[1]);
    Day8::PartTwo(argv[1]);
}
