#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

#include "StringHelp/StringHelp.h"
#include "include/Day9.h"

using namespace std;

void PrintValues(const vector<vector<long>>& vals)
{
    for (auto x : vals)
    {
        for (auto y : x)
        {
            cout << y << "  ";
        }
        cout << "\n";
    }
    cout << "\n\n";
}

int Day9::PartOne(const std::string& file)
{
    std::ifstream dataFile(file);

    if (!dataFile.is_open())
    {
        std::cerr << "Could not open input file '" << file << "'!\n";
        return EXIT_FAILURE;
    }

    string line;
    long long ans = 0;

    while (std::getline(dataFile, line))
    {
        vector<vector<long>> values{};
        vector<string> input =  Helpers::split(line, " ");
        vector<long> ints{};

        // vector<string> --> vector<int>
        for (auto value : input)
        {
            ints.push_back(stoi(value));
        }

        values.push_back(move(ints));

        while (std::any_of(values.back().begin(), values.back().end(), [](long i){return i;}))
        {
            vector<long> current{};
            for (auto it = values.back().begin(); it != values.back().end()-1; it++)
            {
                current.push_back(*(it+1)-*it);
            }
            values.push_back(move(current));
        }

        long val = 0;
        for (auto it = values.rbegin(); it < values.rend(); it++)
        {
            val += (*it).back();
        }
        PrintValues(values);
        cout << val << "\n";
        ans+=val;
    }

    std::cout << "8.1 answer: " << ans << "\n";

    return EXIT_SUCCESS;
}

int Day9::PartTwo(const std::string& file)
{
    std::ifstream dataFile(file);

    if (!dataFile.is_open())
    {
        std::cerr << "Could not open input file '" << file << "'!\n";
        return EXIT_FAILURE;
    }

    string line;
    long long ans = 0;

    while (std::getline(dataFile, line))
    {

    }

    std::cout << "8.2 answer: " << ans << "\n";
    return EXIT_SUCCESS;
}
