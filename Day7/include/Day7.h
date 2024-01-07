#include <map>

namespace Day7{
int PartOne(const std::string& file);
int PartTwo(const std::string& file);
int ScoreOfHand(const std::map<char, int>& cards);
int FindBestHand(std::map<char, int> cards);
}