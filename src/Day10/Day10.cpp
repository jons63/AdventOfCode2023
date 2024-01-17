#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <array>

#include "StringHelp/StringHelp.h"
#include "include/Day10.h"

using namespace std;

struct Coordinate
{
    //Coordinate(const int& row, const int& col, char chr) : row_{row}, col_{col} {};
    int row_;
    int col_;

    Coordinate operator+(const Coordinate& c) const
    {
        return Coordinate{row_ + c.row_, col_ + c.col_};
    }

    bool operator==(const Coordinate& c) const
    {
        return row_ == c.row_ && col_ == c.col_;
    }
};

const array<Coordinate, 4> S{Coordinate{0, 1}, Coordinate{0, -1}, Coordinate{1, 0}, Coordinate{-1, 0}};
const array<Coordinate, 2> Seven {Coordinate{0, -1}, Coordinate{1, 0}};
const array<Coordinate, 2> F {Coordinate{1, 0}, Coordinate{0, 1}};
const array<Coordinate, 2> J {Coordinate{0, -1}, Coordinate{-1, 0}};
const array<Coordinate, 2> L {Coordinate{-1, 0}, Coordinate{0, 1}};
const array<Coordinate, 2> Dash {Coordinate{0, -1}, Coordinate{0, 1}};
const array<Coordinate, 2> Pipe {Coordinate{-1, 0}, Coordinate{1, 0}};

const auto partOneAns = 6786;

const array<Coordinate, 2>& getChar(const char chr)
{
    if (chr == '7') {
        return Seven;
    }
    else if(chr == 'F') {
        return F;
    }
    else if(chr == 'J') {
        return J;
    }
    else if(chr == 'L') {
        return L;
    }
    else if(chr == '-') {
        return Dash;
    } else {
        return Pipe;
    }
}

int Day10::PartOne(const std::string& file)
{
    std::ifstream dataFile(file);

    if (!dataFile.is_open())
    {
        std::cerr << "Could not open input file '" << file << "'!\n";
        return EXIT_FAILURE;
    }

    char arr[140][140];
    uint8_t i{0};
    string line;
    uint64_t ans = 0;
    Coordinate currPos{0,0};

    while (std::getline(dataFile, line))
    {
        line.copy(arr[i], line.length());
        int x = line.find("S");
        if (x != string::npos)
        {
            currPos = Coordinate{i, x};
        }
        i++;
    }

    char current{'S'};
    Coordinate prevPos = currPos;
    for (auto a : S)
    {
        char chr = arr[currPos.row_ + a.row_][currPos.col_ + a.col_];
        if (chr == '7' || '|' || 'F' || 'J' || '-' || 'L')
        {
            auto& connections = getChar(chr);
            if (a + connections[0] == Coordinate{0,0})
            {
                prevPos = currPos;
                currPos = currPos + connections[0];
                ans++;
                break;
            }
            else if (a + connections[1] ==  Coordinate{0,0})
            {
                prevPos = currPos;
                currPos = currPos + connections[1];
                ans++;
                break;
            }
        }
    }

    while (arr[currPos.row_][currPos.col_] != 'S')
    {
        current = arr[currPos.row_][currPos.col_];
        for (auto a : getChar(current))
        {
            Coordinate tmp = currPos + a;
            if (!(tmp == prevPos))
            {
                prevPos = currPos;
                currPos = currPos + a;
                ans++;
                break;
            }
        }
    }

    std::cout << "10.1 answer: " << ans/2 << "\n";
    return EXIT_SUCCESS;
}

int Day10::PartTwo(const std::string& file)
{
    std::ifstream dataFile(file);

    if (!dataFile.is_open())
    {
        std::cerr << "Could not open input file '" << file << "'!\n";
        return EXIT_FAILURE;
    }

    char arr[140][140];
    uint8_t i{0};
    string line;
    uint64_t ans = 0;
    Coordinate currPos{0,0};

    while (std::getline(dataFile, line))
    {
        line.copy(arr[i], line.length());
        int x = line.find("S");
        if (x != string::npos)
        {
            currPos = Coordinate{i, x};
        }
        i++;
    }
    vector<Coordinate> boundaries;

    char current{'S'};
    Coordinate prevPos = currPos;
    for (auto a : S)
    {
        char chr = arr[currPos.row_ + a.row_][currPos.col_ + a.col_];
        if (chr == '7' || '|' || 'F' || 'J' || '-' || 'L')
        {
            auto& connections = getChar(chr);
            if (a + connections[0] == Coordinate{0,0})
            {
                prevPos = currPos;
                currPos = currPos + connections[0];
                ans++;
                boundaries.push_back(currPos);
                break;
            }
            else if (a + connections[1] ==  Coordinate{0,0})
            {
                prevPos = currPos;
                currPos = currPos + connections[1];
                ans++;
                boundaries.push_back(currPos);
                break;
            }
        }
    }

    while (arr[currPos.row_][currPos.col_] != 'S')
    {
        current = arr[currPos.row_][currPos.col_];
        for (auto a : getChar(current))
        {
            Coordinate tmp = currPos + a;
            if (!(tmp == prevPos))
            {
                prevPos = currPos;
                currPos = currPos + a;
                ans++;
                boundaries.push_back(currPos);
                break;
            }
        }
    }

    int area = 0;
    for (auto i = 0; i < boundaries.size()-1; i++)
    {
        area += boundaries[i].col_*boundaries[i+1].row_ - boundaries[i+1].col_*boundaries[i].row_;
    }

    area += boundaries[boundaries.size()-1].col_*boundaries[0].row_ - boundaries[0].col_*boundaries[boundaries.size()-1].row_;

    ans = (area - boundaries.size() +2)/2;

    std::cout << "10.2 answer: " << ans << "\n";

    return EXIT_SUCCESS;
}
