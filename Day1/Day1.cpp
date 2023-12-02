#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <vector>

using namespace std;

int PartOne(const std::string& file)
{
    const string numbers = "0123456789";
    std::ifstream dataFile(file);

    if (!dataFile.is_open())
    {
        std::cerr << "Could not open input file '" << file << "'!\n";
        return EXIT_FAILURE;
    }

    int number = 0;
    std::string line;

    while (std::getline(dataFile, line))
    {
        const size_t first = line.find_first_of(numbers);
        const size_t last = line.find_last_of(numbers);

        std::string name = line.substr(first, 1) + line.substr(last, 1);

        number += stoi(name);
    }

    cout << "1.1 answer: " << number << "\n";
    return EXIT_SUCCESS;
}

int getNumber(vector<string> numbers)
{
    string res = "";
    for (string number : numbers)
    {
        if (number.length() == 1)
        {
            res += number;
        }
        else if(number == "one")
        {
            res += "1";
        }
        else if(number == "two")
        {
            res += "2";
        }
        else if(number == "three")
        {
            res += "3";
        }
        else if(number == "four")
        {
            res += "4";
        }
        else if(number == "five")
        {
            res += "5";
        }
        else if(number == "six")
        {
            res += "6";
        }
        else if(number == "seven")
        {
            res += "7";
        }
        else if(number == "eight")
        {
            res += "8";
        }
        else if(number == "nine")
        {
            res += "9";
        }
        else
        {
            cout << "Could not convert string to number\n";
        }
    }
    return stoi(res);
}

int PartTwo(const std::string& file)
{
    std::regex numberRegex("zero|one|two|three|four|five|six|seven|eight|nine|\\d");
    std::ifstream dataFile(file);

    if (!dataFile.is_open())
    {
        std::cerr << "Could not open input file '" << file << "'!\n";
        return EXIT_FAILURE;
    }

    int number = 0;
    std::string line;
    smatch numberMatch;

    while (std::getline(dataFile, line))
    {
        vector<string> res;
        string::const_iterator searchStart = line.cbegin();
        while (regex_search(searchStart, line.cend(), numberMatch, numberRegex))
        {
            res.push_back(numberMatch[0]);
            searchStart += numberMatch.position() + 1;// numberMatch.suffix().first-1;
        }
        number += getNumber({res[0], res[res.size()-1]});
    }

    cout << "1.2 answer: " << number << "\n";
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