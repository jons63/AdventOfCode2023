#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

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

int FindMirrorPoint(const vector<vector<char>>& vec, int old = -1)
{
    int ans = -1;
    for (int i = 0; i < vec.size()-1; i++)
    {
        if (vec[i] == vec[i+1])
        {
            if (IsMirrored(vec, i) && i != old)
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

vector<vector<char>> Transpose(vector<vector<char>>& pattern)
{
    vector<vector<char>> transposedPattern;
    for (size_t i = 0; i < pattern[0].size(); i++)
    {
        transposedPattern.push_back({});
        for (size_t j = 0; j < pattern.size(); j++)
        {
            transposedPattern[i].push_back(pattern[j][i]);
        }
    }
    return std::move(transposedPattern);
}

void Switch(vector<vector<char>>& pattern, int i, int j)
{
    if (pattern[i][j] == '.')
    {
        pattern[i][j] = '#';
    }
    else
    {
        pattern[i][j] = '.';
    }
}

std::pair<int, int> OldReflection(vector<vector<char>>& pattern)
{
    int row = FindMirrorPoint(pattern);
    if (row != -1)
    {
        return {row,-1};
    }
    vector<vector<char>> transposedPattern = Transpose(pattern);

    int col = FindMirrorPoint(transposedPattern);
    if (col != -1)
    {
        return {-1,col};
    }
    else
    {
        cout << "Failed to find a mirrored row or column\n";
        return {-1, -1};
    }
}

int Day13::PartTwo(const std::string& file)
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

    for (auto pattern : patterns)
    {
        bool next_pattern = false;
        auto old = OldReflection(pattern);
        for (int i = 0; i < pattern.size(); i++)
        {
            for (int j = 0; j < pattern[0].size(); j++)
            {
                Switch(pattern, i, j);

                int row = FindMirrorPoint(pattern, old.first);
                if (row != -1 && row != old.first)
                {
                    ans += (row+1)*100;
                    next_pattern = true;
                    break;
                }
                vector<vector<char>> transposedPattern = Transpose(pattern);
                int col = FindMirrorPoint(transposedPattern, old.second);
                if (col != -1 && col != old.second)
                {
                    ans += col+1;
                    next_pattern = true;
                }

                if (next_pattern)
                {
                    break;
                }
                Switch(pattern, i, j);
            }
            if (next_pattern)
            {
                break;
            }
        }
        if (!next_pattern)
        {
            cout << "Failed to find a mirrored row or column\n";
            return EXIT_FAILURE;
        }
    }

    std::cout << "13.2 answer: " << ans << "\n";
    return EXIT_SUCCESS;
}

int GetPatternScore(std::vector<uint64_t> rows_or_colls, uint8_t factor, uint8_t diff) {
    for (auto i = 0; i < rows_or_colls.size()-1; i++) {
        auto diffs = 0;
        for (auto r_index = i, index = i+1; r_index >= 0 && index < rows_or_colls.size(); --r_index, ++index) {
            diffs += __builtin_popcount(rows_or_colls[r_index] ^ rows_or_colls[index]);
        }
        if (diffs == diff) {
            return (i+1)*factor;
        }
    }
    return 0;
}

int Day13::CompactSolution(const std::string& file)
{
    std::ifstream dataFile(file);

    if (!dataFile.is_open())
    {
        std::cerr << "Could not open input file '" << file << "'!\n";
        return EXIT_FAILURE;
    }

    string line;
    std::vector<uint64_t> rows;
    std::vector<uint64_t> cols;

    uint64_t ans1{0};
    uint64_t ans2{0};

    while (std::getline(dataFile, line))
    {
        uint64_t row{0};
        if (cols.empty()) {
            cols.resize(line.length());
        }
        if (!line.empty()) {
            const auto col = rows.size();
            for (auto i = 0; i < line.length(); i++) {
                const bool bit = line[i] == '#';
                row |= bit << i;
                cols[i] |= bit << col;
            }
            rows.push_back(row);
        } else {
            ans1 += GetPatternScore(rows, 100, 0);
            ans1 += GetPatternScore(cols, 1, 0);

            ans2 += GetPatternScore(rows, 100, 1);
            ans2 += GetPatternScore(cols, 1, 1);

            cols.clear();
            rows.clear();
        }
    }

    std::cout << "13.1 answer: " << ans1 << "\n";
    std::cout << "13.2 answer: " << ans2 << "\n";
    return EXIT_SUCCESS;
}
