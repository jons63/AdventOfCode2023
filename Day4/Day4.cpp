#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <cmath>
#include <array>

#include "StringHelp/StringHelp.h"

using namespace std;

int PartOne(const std::string& file)
{
    int ans = 0;

    std::ifstream dataFile(file);

    if (!dataFile.is_open())
    {
        std::cerr << "Could not open input file '" << file << "'!\n";
        return EXIT_FAILURE;
    }

    std::string line;

    while (std::getline(dataFile, line))
    {
        set<int> winningNumbers;
        int matches = 0;

        string numbers = Helpers::split(line, ":").back();
        auto tmp = Helpers::split(numbers, "|");
        auto winningNumbersString = Helpers::split(tmp[0], " ");
        auto cardNumbers = Helpers::split(tmp[1], " ");

        for (auto val : winningNumbersString)
        {
            winningNumbers.emplace(stoi(val));
        }

        for (auto val : cardNumbers)
        {
            if (winningNumbers.count(stoi(val)) > 0)
            {
                matches++;
            }
        }

        if (matches)
        {
            ans += 1*pow(2,matches-1);
        }
    }

    std::cout << "4.1 answer: " << ans << "\n";
    return EXIT_SUCCESS;
}


int PartTwo(const std::string& file)
{
    long ans = 0;
    array<long, 192> cards{1};
    cards.fill(1);

    std::ifstream dataFile(file);

    if (!dataFile.is_open())
    {
        std::cerr << "Could not open input file '" << file << "'!\n";
        return EXIT_FAILURE;
    }

    std::string line;

    while (std::getline(dataFile, line))
    {
        set<int> winningNumbers;
        int matches = 0;

        auto numbers = Helpers::split(line, ":");
        int card = stoi(Helpers::split(numbers[0], " ")[1]) - 1;

        auto tmp = Helpers::split(numbers[1], "|");
        auto winningNumbersString = Helpers::split(tmp[0], " ");
        auto cardNumbers = Helpers::split(tmp[1], " ");

        for (auto val : winningNumbersString)
        {
            winningNumbers.emplace(stoi(val));
        }

        for (auto val : cardNumbers)
        {

            if (winningNumbers.count(stoi(val)) > 0)
            {
                matches++;
            }
        }

        for (int i = 1; (i <= matches) && ((i + card) < 192); i++)
        {
            long tmp = cards[i + card] + cards[card];
            cards[i + card] = tmp;
        }
    }

    for (auto card : cards)
    {
        ans += card;
    }

    cout << "4.2 answer: " << ans << "\n";
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{

    if (argc < 2) {
        std::cerr << "Missing input file!\n";
        return EXIT_FAILURE;
    }

    PartOne(argv[1]);
    PartTwo(argv[1]);
}