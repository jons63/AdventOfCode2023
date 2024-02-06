#include <fstream>
#include <iostream>
#include <string>
#include <vector>
//#include <array>
//#include <algorithm>
//#include <map>
#include <utility>

#include "StringHelp/StringHelp.h"
#include "include/Day13.h"

using namespace std;

int IsMirrored(const vector<vector<char>>& vec, int startPos)
{
    int i = 1;
    while (startPos-i > -1 && startPos+i+1 < vec.size())
    {
        if (vec[startPos-i] != vec[startPos+i+1])
        {
            return false;
        }
        i++;
    }
    return true;
}

int FindMirrorPoint(const vector<vector<char>>& vec)
{
    int ans = -1;
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] == vec[i+1])
        {
            if (IsMirrored(vec, i))
            {
                return i;
            }
        }
    }
    return -1;
}

int Day13::PartOne(const std::string& file)
{
    std::ifstream dataFile(file);

    if (!dataFile.is_open())
    {
        std::cerr << "Could not open input file '" << file << "'!\n";
        return EXIT_FAILURE;
    }

    vector<vector<vector<char>>> patterns = {};

    string line;
    uint64_t ans = 0;

    vector<vector<char>> pattern;
    while (std::getline(dataFile, line))
    {
        if (line.empty())
        {
            patterns.push_back(pattern);
            pattern.clear();
        }
        else
        {
            pattern.emplace_back(line.begin(), line.end());
        }
    }
    patterns.push_back(pattern);

    for (vector<vector<char>> pattern : patterns)
    {
        int row = FindMirrorPoint(pattern);
        if (row != -1)
        {
            ans += (row+1)*100;
            continue;
        }
        vector<vector<char>> transposedPattern;
        for (size_t i = 0; i < pattern[0].size(); i++)
        {
            transposedPattern.push_back({});
            for (size_t j = 0; j < pattern.size(); j++)
            {
                transposedPattern[i].push_back(pattern[j][i]);
            }
        }
        int col = FindMirrorPoint(transposedPattern);
        if (col != -1)
        {
            ans += col+1;
        }
        else
        {
            cout << "Failed to find a mirrored row or column\n";
            return EXIT_FAILURE;
        }
    }

    std::cout << "13.1 answer: " << ans << "\n";
    return EXIT_SUCCESS;
}

//40963 to high

int Day13::PartTwo(const std::string& file)
{
    std::ifstream dataFile(file);

    if (!dataFile.is_open())
    {
        std::cerr << "Could not open input file '" << file << "'!\n";
        return EXIT_FAILURE;
    }

    string line;
    uint64_t ans = 0;

    while (std::getline(dataFile, line))
    {

    }

    std::cout << "13.2 answer: " << ans << "\n";
    return EXIT_SUCCESS;
}
