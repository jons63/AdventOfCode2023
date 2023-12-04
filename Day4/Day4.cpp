#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <cmath>
#include <array>

using namespace std;

vector<string> split(string str, const string& delimiter)
{
    size_t delimiterPos = 0;
    vector<string> parts{};
    while ((delimiterPos = str.find(delimiter)) != str.npos)
    {
        if (delimiterPos)
        {
            string subStr = str.substr(0, delimiterPos);
            if (subStr != delimiter || subStr != "\n" && !subStr.empty())
            {
                parts.push_back(subStr);
            }
        }
        str.erase(0, delimiterPos+1);
    }
    if (!str.empty())
    {
        parts.push_back(str);
    }
    return parts;
}

void strip(string& str)
{
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
}

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

        string numbers = split(line, ":").back();
        auto tmp = split(numbers, "|");
        auto winningNumbersString = split(tmp[0], " ");
        auto cardNumbers = split(tmp[1], " ");

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

        auto numbers = split(line, ":");
        int card = stoi(split(numbers[0], " ")[1]) - 1;

        auto tmp = split(numbers[1], "|");
        auto winningNumbersString = split(tmp[0], " ");
        auto cardNumbers = split(tmp[1], " ");

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