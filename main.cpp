#include <iostream>

#include "include/Day8.h"
#include "include/Day9.h"
#include "include/Day10.h"
#include "include/Day11.h"
#include "include/Day12.h"
#include "include/Day13.h"

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

    //Day10::PartOne(argv[1]);
    //Day10::PartTwo(argv[1]);

    //Day11::PartOne(argv[1]);
    //Day11::PartTwo(argv[1]);

    //Day12::PartOne(argv[1]);
    //Day12::PartTwo(argv[1]);

    Day13::PartOne(argv[1]);
    Day13::PartTwo(argv[1]);

    Day13::CompactSolution(argv[1]);
}
