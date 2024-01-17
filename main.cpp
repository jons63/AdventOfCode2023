#include <iostream>

#include "include/Day8.h"
#include "include/Day9.h"
#include "include/Day10.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cerr << "Missing input file!\n";
        return EXIT_FAILURE;
    }

    //Day8::PartOne(argv[1]);
    //Day8::PartTwo(argv[1]);

    //Day9::PartOne(argv[1]);
    //Day9::PartTwo(argv[1]);

    Day10::PartOne(argv[1]);
    Day10::PartTwo(argv[1]);
}
