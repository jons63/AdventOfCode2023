#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

struct Index
{
    int x_;
    int y_;

    bool operator< (const Index& index) const
    {
        if (x_ < index.x_)
        {
            return true;
        }
        else if (x_ > index.x_)
        {
            return false;
        }
        else
        {
            if (y_ < index.y_)
            {
                return true;
            }
            else if (y_ >= index.y_)
            {
                return false;
            }
        }
        return false;
    }
};

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
    set<Index> symbols;
    vector<pair<string, vector<Index>>> values;
    int lineNum = -1;

    while (std::getline(dataFile, line))
    {
        lineNum++;
        string number = "";
        vector<Index> numberIndexes;
        for (int i = 0; i < line.length(); i++)
        {
            if ('0' <= line[i] && line[i] <= '9')
            {
               number += string{line[i]};
               numberIndexes.push_back({lineNum, i});
               if(!('0' <= line[i+1] && line[i+1] <= '9'))
               {
                    values.emplace_back(pair<string, vector<Index>>(number, numberIndexes));
                    number = "";
                    numberIndexes.clear();
               }
            }
            else if ('.' == line[i] || '\n' == line[i]) {}
            else
            {
                symbols.insert({lineNum, i});
            }
        }
    }

    for (auto value : values)
    {
        bool brk = false;
        for (int x = value.second[0].x_ - 1; x < value.second[0].x_ + 2; x++)
        {
            for (int y = value.second[0].y_ - 1; y < value.second[0].y_ + static_cast<int>(value.second.size()) + 1; y++)
            {
                if (0 < symbols.count({x, y}))
                {
                    ans += stoi(value.first);
                    brk = true;
                    break;
                }
            }
            if (brk)
            {
                break;
            }
        }
    }
    cout << "3.1 answer: " << ans << "\n";
    return EXIT_SUCCESS;
}


int PartTwo(const std::string& file)
{
    int ans = 0;

    std::ifstream dataFile(file);

    if (!dataFile.is_open())
    {
        std::cerr << "Could not open input file '" << file << "'!\n";
        return EXIT_FAILURE;
    }

    std::string line;
    map<Index, vector<int>> symbols;
    vector<pair<string, vector<Index>>> values;
    int lineNum = -1;

    while (std::getline(dataFile, line))
    {
        lineNum++;
        string number = "";
        vector<Index> numberIndexes;
        for (int i = 0; i < line.length(); i++)
        {
            if ('0' <= line[i] && line[i] <= '9')
            {
               number += string{line[i]};
               numberIndexes.push_back({lineNum, i});
               if(!('0' <= line[i+1] && line[i+1] <= '9'))
               {
                    values.emplace_back(pair<string, vector<Index>>(number, numberIndexes));
                    number = "";
                    numberIndexes.clear();
               }
            }
            else if ('.' == line[i] || '\n' == line[i]) {}
            else
            {
                symbols.emplace(Index{lineNum, i}, vector<int>{});
            }
        }
    }

    for (auto value : values)
    {
        bool brk = false;
        for (int x = value.second[0].x_ - 1; x < value.second[0].x_ + 2; x++)
        {
            for (int y = value.second[0].y_ - 1; y < value.second[0].y_ + static_cast<int>(value.second.size()) + 1; y++)
            {
                if (0 < symbols.count({x, y}))
                {
                    symbols[{x,y}].push_back(stoi(value.first));
                    brk = true;
                    break;
                }
            }
            if (brk)
            {
                break;
            }
        }
    }

    for (auto symbol : symbols)
    {
        if (symbol.second.size() == 2)
        {
            ans += (symbol.second[0]*symbol.second[1]);
        }
    }
    cout << "3.2 answer: " << ans << "\n";
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