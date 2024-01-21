#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <map>
#include <utility>

#include "StringHelp/StringHelp.h"
#include "include/Day12.h"

using namespace std;

uint64_t DynamicProgramming(const string& hotsprings,
                       const vector<int>& groups,
                       int currentHotspringPos,
                       int currentGroup,
                       int currentGroupLength);

vector<string> CreatePermutations(string str)
{
    auto pos = str.find('?');

    if (pos != string::npos)
    {
        auto dotVec = CreatePermutations(str.substr(pos+1, str.size()-pos));
        auto hashVec = dotVec;
        for (string& s : dotVec)
        {
            s = str.substr(0, pos)+"#"+s;
        }
        for (string& s : hashVec)
        {
            s = str.substr(0, pos)+"."+s;
        }
        dotVec.insert(dotVec.cend(), hashVec.begin(), hashVec.end());
        return dotVec;
    }
    else
    {
        return {str};
    }
}

int Day12::PartOne(const std::string& file)
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
        int combinations = 0;
        vector<string> vec = Helpers::split(line, " ");
        vector<string> hotspringGroups = Helpers::split(vec[1], ",");
        auto hotspringPermutations = CreatePermutations(vec[0]);

        for (auto permutation : hotspringPermutations)
        {
            auto damagedHotspringGrups = Helpers::split(permutation, ".");
            if (damagedHotspringGrups.size() == hotspringGroups.size())
            {
                bool b = true;
                for (size_t i = 0; i < hotspringGroups.size(); i++)
                {
                    if (stoi(hotspringGroups[i]) != damagedHotspringGrups[i].size())
                    {
                        b = false;
                    }
                }
                if (b) {
                    combinations++;
                }
            }
        }
        ans+=combinations;
    }

    std::cout << "12.1 answer: " << ans << "\n";
    return EXIT_SUCCESS;
}

struct Key
{
    Key(int currentHotspringPos,
        int currentGroup,
        int currentGroupLength) :
        currentHotspringPos_{currentHotspringPos},
        currentGroup_{currentGroup},
        currentGroupLength_{currentGroupLength} {};

    int currentHotspringPos_;
    int currentGroup_;
    int currentGroupLength_;
};

struct KeyCompare
{
    bool operator() (const Key& lhs, const Key& rhs) const {
        if (lhs.currentHotspringPos_ < rhs.currentHotspringPos_) {
            return true;
        } else if (lhs.currentHotspringPos_ == rhs.currentHotspringPos_) {
            if (lhs.currentGroup_ < rhs.currentGroup_) {
                return true;
            } else if (lhs.currentGroup_ == rhs.currentGroup_) {
                return lhs.currentGroupLength_ < rhs.currentGroupLength_;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
};

map<Key, uint64_t, KeyCompare> memmory;

uint64_t DynamicProgramming(const string& hotsprings,
                       const vector<int>& groups,
                       int currentHotspringPos,
                       int currentGroup,
                       int currentGroupLength)
{
    if (memmory.count(Key{currentHotspringPos, currentGroup, currentGroupLength})) {
        return memmory[Key{currentHotspringPos, currentGroup, currentGroupLength}];
    }

    if (currentHotspringPos == hotsprings.size()) {
        if (groups.size() == currentGroup && currentGroupLength == 0) {
            // Found valid sequence, sequence ends in #
            return 1;
        } else if (groups.size()-1 == currentGroup && groups[currentGroup] == currentGroupLength) {
            // Found valid sequence, sequence ends in .
            return 1;
        } else {
            // Did not find valid sequence
            return 0;
        }
    }

    uint64_t ans = 0;
    for (char c : {'.', '#'}) {
        if (hotsprings[currentHotspringPos] == '?' || hotsprings[currentHotspringPos] == c) {

            if (currentGroupLength == 0 && c == '.') {
                // If no group and . -> keep goning
                ans += DynamicProgramming(hotsprings, groups, currentHotspringPos+1, currentGroup, 0);
            }
            //else if (currentGroupLength ==  groups[currentGroup] && c == '.') {
            else if (currentGroupLength > 0 && c == '.' && currentGroup < groups.size() && groups[currentGroup] == currentGroupLength) {
                // Found fitting group, start search for next group
                ans += DynamicProgramming(hotsprings, groups, currentHotspringPos+1, currentGroup+1, 0);
            }
            else if (c == '#') {
                // add hotspring to group
                ans += DynamicProgramming(hotsprings, groups, currentHotspringPos+1, currentGroup, currentGroupLength+1);;
            }
        }
    }

    memmory[Key{currentHotspringPos, currentGroup, currentGroupLength}] = ans;
    return ans;
}

int Day12::PartTwo(const std::string& file)
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
        vector<string> vec = Helpers::split(line, " ");
        string hotsprings = vec[0]+"?"+vec[0]+"?"+vec[0]+"?"+vec[0]+"?"+vec[0];
        vector<string> tmp = Helpers::split(vec[1], ",");
        vector<string> tmp2 = tmp;

        tmp2.insert(tmp2.cend(), tmp.begin(), tmp.end());
        tmp2.insert(tmp2.cend(), tmp.begin(), tmp.end());
        tmp2.insert(tmp2.cend(), tmp.begin(), tmp.end());
        tmp2.insert(tmp2.cend(), tmp.begin(), tmp.end());

        vector<int> hotspringGroups;

        std::for_each(tmp2.begin(), tmp2.end(), [&](string s){hotspringGroups.push_back(stoi(s));});
        memmory.clear();
        uint64_t score = DynamicProgramming(hotsprings, hotspringGroups, 0, 0, 0);

        ans += score;
    }

    std::cout << "12.2 answer: " << ans << "\n";
    return EXIT_SUCCESS;
}
