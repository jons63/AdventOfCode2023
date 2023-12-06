#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int func(pair<uint64_t, uint64_t> data)
{
    auto eq = [data](uint64_t val){return (data.first * val - pow(val, 2)) > data.second;};
    for (uint64_t i = 0; i < data.first; i++)
    {
        if (eq(i))
        {
            return data.first+1 - (2 * i);
        }
    }
    return 0;
}

void PartOne()
{
    int ans = 1;

    vector<pair<int, int>> input = {{41, 244}, {66, 1047}, {72, 1228}, {66,1040}};

    for (auto data : input)
    {
        ans *= func(data);
    }

    std::cout << "6.1 answer: " << ans << "\n";
}


void PartTwo()
{
    uint64_t ans = 1;
    pair<uint64_t, uint64_t> data = {41667266, 244104712281040};

    ans = func(data);

    cout << "6.2 answer: " << ans << "\n";
}

int main()
{
    PartOne();
    PartTwo();
}