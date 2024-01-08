#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>

#include "include/Day8.h"
#include "StringHelp/StringHelp.h"

using namespace std;


int Day8::PartOne(const std::string& file)
{
    std::ifstream dataFile(file);

    if (!dataFile.is_open())
    {
        std::cerr << "Could not open input file '" << file << "'!\n";
        return EXIT_FAILURE;
    }

    string line;
    string moves;
    string node{"AAA"};

    std::getline(dataFile, moves);
    // thorw away an empty line
    std::getline(dataFile, line);

    map<string, pair<string, string>> network;

    while (std::getline(dataFile, line))
    {
        string key = line.substr(0,3);
        string left = line.substr(7,3);
        string right = line.substr(12,3);

        network.emplace(key, pair<string, string>{left, right});
    }

    pair<string, string> move = network[node];
    uint64_t numOfMoves{0};
    bool continueMoving = true;

    while(continueMoving)
    {
        auto it = moves.begin();
        while(it != moves.end())
        {
            if (*it == 'L')
            {
                node = network[node].first;
            }
            else
            {
                node = network[node].second;
            }
            numOfMoves++;
            it++;
            if (node == "ZZZ")
            {
                continueMoving = false;
                break;
            }
        }
    }

    std::cout << "8.1 answer: " << numOfMoves << "\n";

    return EXIT_SUCCESS;
}

bool endsInZ(string& p)
{
    if (p[2] == 'Z')
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Day8::PartTwo(const std::string& file)
{
    std::ifstream dataFile(file);

    if (!dataFile.is_open())
    {
        std::cerr << "Could not open input file '" << file << "'!\n";
        return EXIT_FAILURE;
    }

    string line;
    string moves;
    vector<string> nodes;

    std::getline(dataFile, moves);
    // thorw away an empty line
    std::getline(dataFile, line);

    map<string, pair<string, string>> network;

    while (std::getline(dataFile, line))
    {
        string key = line.substr(0,3);
        string left = line.substr(7,3);
        string right = line.substr(12,3);

        if (key[2] == 'A')
        {
            nodes.push_back(key);
        }
        network.emplace(key, pair<string, string>{left, right});
    }

    uint64_t numOfMoves{0};
    bool continueMoving = true;

    while(continueMoving)
    {
        auto it = moves.begin();
        while(it != moves.end())
        {
            if (*it == 'L')
            {
                for (string& node : nodes)
                {
                    node =  network[node].first;
                }
            }
            else
            {
                for (string& node : nodes)
                {
                    node =  network[node].second;
                }
            }
            numOfMoves++;
            it++;
            if (std::all_of(nodes.begin(), nodes.end(), endsInZ))
            {
                continueMoving = false;
                break;
            }
            if (numOfMoves % 1000000 == 0)
            {
                cout << numOfMoves << "\n";
            }
        }
    }

    std::cout << "8.2 answer: " << numOfMoves << "\n";
    return EXIT_SUCCESS;
}