#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>

#include "StringHelp/StringHelp.h"

#include "../include/Day7.h"

using namespace std;

using Hand = pair<string, uint64_t>;

enum CardValue
{
};

int Day7::PartOne(const std::string& file)
{
    int ans = 0;
    vector<Hand> hands;

    std::ifstream dataFile(file);

    if (!dataFile.is_open())
    {
        std::cerr << "Could not open input file '" << file << "'!\n";
        return EXIT_FAILURE;
    }

    std::string line;

    while (std::getline(dataFile, line))
    {
        auto vals = Helpers::split(line, " ");
        for (auto it = vals[0].begin(); it != vals[0].end(); it++)
        {
            if (*it == 'T')
            {
                *it = 'A';
            }
            else if (*it == 'J')
            {
                *it = 'B';
            }
            else if (*it == 'Q')
            {
                *it = 'C';
            }
            else if (*it == 'K')
            {
                *it = 'D';
            }
            else if (*it == 'A')
            {
                *it = 'E';
            }
        }
        hands.emplace_back(Hand{vals[0], stoi(vals[1])});
    }

    std::sort(hands.begin(), hands.end(), [](const Hand& first, const Hand& second)
        {
            bool ret = false;
            uint64_t firstScore = 0;
            uint64_t secondScore = 0;
            map<char, int> firstHand;
            map<char, int> secondHand;
            auto func = [&](char ch){firstHand[ch]++;};
            std::for_each(first.first.begin(), first.first.end(), func);
            auto func2 = [&](char ch){secondHand[ch]++;};
            std::for_each(second.first.begin(), second.first.end(), func2);

            auto func3 = [&](pair<char, int> num){firstScore += exp10(num.second);};
            std::for_each(firstHand.begin(), firstHand.end(), func3);
            auto func4 = [&](pair<char, int> num){secondScore +=exp10(num.second);};
            std::for_each(secondHand.begin(), secondHand.end(), func4);

            if (firstScore == secondScore)
            {
                for (auto it = first.first.begin(), it2 = second.first.begin(); it != first.first.end(); it++, it2++)
                {
                    if (*it > *it2)
                    {
                        ret = false;
                        break;
                    }
                    else if (*it < *it2)
                    {
                        ret = true;
                        break;
                    }
                }
            }
            else
            {
                firstScore > secondScore ? ret = false : ret = true;
            }

            return ret;
        });

    for (auto i = 0; i < hands.size(); i++)
    {
        ans += hands[i].second * (i+1);
    }

    std::cout << "7.1 answer: " << ans << "\n";

    return EXIT_SUCCESS;
}

int Day7::ScoreOfHand(const map<char, int>& cards)
{
    int score = 0;
    for (auto card : cards)
    {
        score += exp10(card.second);
    }
    return score;
}

int Day7::FindBestHand(map<char, int> originalHand)
{
    int score = 0;

    if (originalHand.count('1') && originalHand['1'] != 5)
    {
        int numOfJokers = originalHand['1'];
        map<char, int> modifiedHand;
        for (auto t : originalHand)
        {
            if (t.first != '1')
            {
                modifiedHand.emplace(t);
            }
        }
        for (auto& t2 : modifiedHand)
        {
            t2.second += numOfJokers;
            int tmp_score = ScoreOfHand(modifiedHand);
            if (tmp_score > score)
            {
                score = tmp_score;
            }
            t2.second -= numOfJokers;
        }
    }
    else
    {
        score = ScoreOfHand(originalHand);
    }

    return score;
}

int Day7::PartTwo(const std::string& file)
{
    int ans = 0;
    vector<Hand> hands;

    std::ifstream dataFile(file);

    if (!dataFile.is_open())
    {
        std::cerr << "Could not open input file '" << file << "'!\n";
        return EXIT_FAILURE;
    }

    std::string line;

    while (std::getline(dataFile, line))
    {
        auto vals = Helpers::split(line, " ");
        // Convet so that higher card value == larger char
        for (auto it = vals[0].begin(); it != vals[0].end(); it++)
        {
            if (*it == 'T')
            {
                *it = 'A';
            }
            else if (*it == 'J')
            {
                *it = '1';
            }
            else if (*it == 'Q')
            {
                *it = 'C';
            }
            else if (*it == 'K')
            {
                *it = 'D';
            }
            else if (*it == 'A')
            {
                *it = 'E';
            }
        }
        hands.emplace_back(Hand{vals[0], stoi(vals[1])});
    }

    std::sort(hands.begin(), hands.end(), [](const Hand& first, const Hand& second)
        {
            bool ret = false;
            map<char, int> firstHand;
            map<char, int> secondHand;

            auto func = [&](char ch){firstHand[ch]++;};
            std::for_each(first.first.begin(), first.first.end(), func);
            auto func2 = [&](char ch){secondHand[ch]++;};
            std::for_each(second.first.begin(), second.first.end(), func2);

            uint64_t score = FindBestHand(firstHand);
            uint64_t score2 = FindBestHand(secondHand);

            if (score == score2)
            {
                for (auto it = first.first.begin(), it2 = second.first.begin(); it != first.first.end(); it++, it2++)
                {
                    if (*it > *it2)
                    {
                        ret = false;
                        break;
                    }
                    else if (*it < *it2)
                    {
                        ret = true;
                        break;
                    }
                }
            }
            else
            {
                score > score2 ? ret = false : ret = true;
            }

            return ret;
        });

    for (auto i = 0; i < hands.size(); i++)
    {
        ans += hands[i].second * (i+1);
    }

    std::cout << "7.2 answer: " << ans << "\n";
    return EXIT_SUCCESS;
}