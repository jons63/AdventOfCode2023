#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>

#include "StringHelp/StringHelp.h"
#include "include/Day11.h"

using namespace std;

struct Galaxy
{
    int y;
    int x;
};

int Day11::PartOne(const std::string& file)
{
    std::ifstream dataFile(file);

    if (!dataFile.is_open())
    {
        std::cerr << "Could not open input file '" << file << "'!\n";
        return EXIT_FAILURE;
    }

    string line;
    uint64_t ans = 0;

    vector<Galaxy> galaxys;
    vector<string> universe;

    while (std::getline(dataFile, line))
    {
        universe.push_back(line);
    }

    for (int y = universe.size()-1; y >= 0; y--)
    {
        for (int x = universe[y].size()-1; x >= 0; x--)
        {
            if (universe[y][x] == '#')
            {
                galaxys.emplace_back(Galaxy{y,x});
            }
        }
    }

    for (int y = universe.size()-1; y >= 0; y--)
    {
        if (universe[y].find('#') == string::npos)
        {
            for (Galaxy& gal : galaxys)
            {
                if (gal.y > y)
                {
                    gal.y++;
                }
            }
        }
    }

    for (int x = universe[0].size()-1; x >= 0; x--)
    {
        if (std::all_of(universe.begin(), universe.end(), [x](string s){return s[x] != '#';}))
        {
            for (Galaxy& gal : galaxys)
            {
                if (gal.x > x)
                {
                    gal.x++;
                }
            }
        }
    }

    for (int x = 0; x < galaxys.size()-1; x++)
    {
        for (int y = x+1; y < galaxys.size(); y++)
        {
            ans += abs(galaxys[x].x-galaxys[y].x)+abs(galaxys[x].y-galaxys[y].y);
        }
    }
    std::cout << "11.1 answer: " << ans << "\n";
    return EXIT_SUCCESS;
}

int Day11::PartTwo(const std::string& file)
{
    std::ifstream dataFile(file);

    if (!dataFile.is_open())
    {
        std::cerr << "Could not open input file '" << file << "'!\n";
        return EXIT_FAILURE;
    }

    string line;
    uint64_t ans = 0;

    vector<Galaxy> galaxys;
    vector<string> universe;

    while (std::getline(dataFile, line))
    {
        universe.push_back(line);
    }

    for (int y = universe.size()-1; y >= 0; y--)
    {
        for (int x = universe[y].size()-1; x >= 0; x--)
        {
            if (universe[y][x] == '#')
            {
                galaxys.emplace_back(Galaxy{y,x});
            }
        }
    }

    for (int y = universe.size()-1; y >= 0; y--)
    {
        if (universe[y].find('#') == string::npos)
        {
            for (Galaxy& gal : galaxys)
            {
                if (gal.y > y)
                {
                    gal.y+=999999;
                }
            }
        }
    }

    for (int col = universe[0].size()-1; col >= 0; col--)
    {
        if (std::all_of(universe.begin(), universe.end(), [col](string s){return s[col] != '#';}))
        {
            for (Galaxy& gal : galaxys)
            {
                if (gal.x > col)
                {
                    gal.x+=999999;
                }
            }
        }
    }

    for (int x = 0; x < galaxys.size()-1; x++)
    {
        for (int y = x+1; y < galaxys.size(); y++)
        {
            ans += abs(galaxys[x].x-galaxys[y].x)+abs(galaxys[x].y-galaxys[y].y);
        }
    }
    std::cout << "11.2 answer: " << ans << "\n";
    return EXIT_SUCCESS;
}
