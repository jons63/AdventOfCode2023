#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int PartOne(const std::string& file)
{
    const int maxRed = 12;
    const int maxGreen = 13;
    const int maxBlue = 14;

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
        size_t delimiterPos = line.find(':');
        const int id = stoi(line.substr(5, delimiterPos-5));
        line.erase(0, delimiterPos+1);
        vector<string> games;
        while ((delimiterPos = line.find(";")) != line.npos)
        {
            auto game = line.substr(0, delimiterPos);
            games.push_back(game + ",");
            line.erase(0, delimiterPos+1);
        }
        games.push_back(line + ",");

        bool valid = true;

        for (auto game : games)
        {
            int red = 0;
            int green = 0;
            int blue = 0;

            while ((delimiterPos = game.find(",")) != game.npos)
            {
                auto cubes = game.substr(0, delimiterPos);
                game.erase(0, delimiterPos+1);
                if ((delimiterPos = cubes.find("red"))!= cubes.npos)
                {
                    red = stoi(cubes.substr(1, delimiterPos-1));
                }
                else if ((delimiterPos = cubes.find("green"))!= cubes.npos)
                {
                    green = stoi(cubes.substr(1, delimiterPos-1));
                }
                else if ((delimiterPos = cubes.find("blue"))!= cubes.npos)
                {
                    blue = stoi(cubes.substr(1, delimiterPos-1));
                }
            }
            if (red > maxRed || green > maxGreen || blue > maxBlue)
            {
                valid = false;
            }
        }

        if (valid)
        {
            ans += id;
        }

    }
    cout << "1.1 answer: " << ans << "\n";
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

    while (std::getline(dataFile, line))
    {
        size_t delimiterPos = line.find(':');
        const int id = stoi(line.substr(5, delimiterPos-5));
        line.erase(0, delimiterPos+1);
        vector<string> games;
        while ((delimiterPos = line.find(";")) != line.npos)
        {
            auto game = line.substr(0, delimiterPos);
            games.push_back(game + ",");
            line.erase(0, delimiterPos+1);
        }
        games.push_back(line + ",");

        int maxRed = 0;
        int maxGreen = 0;
        int maxBlue = 0;

        for (auto game : games)
        {
            int red = 0;
            int green = 0;
            int blue = 0;

            while ((delimiterPos = game.find(",")) != game.npos)
            {
                auto cubes = game.substr(0, delimiterPos);
                game.erase(0, delimiterPos+1);
                if ((delimiterPos = cubes.find("red"))!= cubes.npos)
                {
                    red = stoi(cubes.substr(1, delimiterPos-1));
                }
                else if ((delimiterPos = cubes.find("green"))!= cubes.npos)
                {
                    green = stoi(cubes.substr(1, delimiterPos-1));
                }
                else if ((delimiterPos = cubes.find("blue"))!= cubes.npos)
                {
                    blue = stoi(cubes.substr(1, delimiterPos-1));
                }
            }
            if (red > maxRed) {maxRed = red;}
            if (green > maxGreen) {maxGreen = green;}
            if (blue > maxBlue) {maxBlue = blue;}
        }
        ans += maxRed*maxGreen*maxBlue;
    }
    cout << "1.2 answer: " << ans << "\n";
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