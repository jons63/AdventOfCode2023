#include <vector>
#include <string>
#include <algorithm>

#include "StringHelp/StringHelp.h"

using namespace std;

vector<string> Helpers::split(string str, const string& delimiter)
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

void Helpers::strip(string& str)
{
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
}