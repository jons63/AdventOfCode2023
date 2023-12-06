#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <cmath>
#include <array>
#include <climits>

using namespace std;

struct Map
{
    long long source;
    long long dest;
    long long range;
};

enum InputParts
{
    Seeds,
    SeedToSoil,
    SoilToFirtilizer,
    FirtilizerToWater,
    WaterToLight,
    LightToTemperature,
    TemperatureToHumidity,
    HumidityToLocation
};

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

void getMapData(vector<Map>& inp, string line)
{
    vector<string> values = split(line, " ");
    long long dest = stoll(values[0]);
    long long source = stoll(values[1]);
    long long range = stoll(values[2]);
    inp.emplace_back(Map{source, dest, range});
}

int PartOne(const std::string& file)
{
    long long ans = LLONG_MAX;

    std::ifstream dataFile(file);

    if (!dataFile.is_open())
    {
        std::cerr << "Could not open input file '" << file << "'!\n";
        return EXIT_FAILURE;
    }

    std::string line;
    int inputPart = InputParts::Seeds;
    set<long long> seeds;

    vector<Map> seedToSoil;
    vector<Map> soilToFirtilizer;
    vector<Map> firtilizerToWater;
    vector<Map> waterToLight;
    vector<Map> lightToTemperature;
    vector<Map> temperatureToHumidity;
    vector<Map> humidityToLocation;

    while (std::getline(dataFile, line))
    {
        if (line.empty())
        {
            inputPart++;
        }
        else if (line.find("map:") != line.npos) {}
        else if (inputPart == InputParts::Seeds)
        {
            string seedsStr = split(line, ":")[1];
            vector<string> seedsVec = split(seedsStr, " ");
            for (auto seed : seedsVec)
            {
                seeds.emplace(stoll(seed));
            }
        }
        else if (inputPart == InputParts::SeedToSoil)
        {
            getMapData(seedToSoil, line);
        }
        else if (inputPart == InputParts::SoilToFirtilizer)
        {
            getMapData(soilToFirtilizer, line);
        }
        else if (inputPart == InputParts::FirtilizerToWater)
        {
            getMapData(firtilizerToWater, line);
        }
        else if (inputPart == InputParts::WaterToLight)
        {
            getMapData(waterToLight, line);
        }
        else if (inputPart == InputParts::LightToTemperature)
        {
            getMapData(lightToTemperature, line);
        }
        else if (inputPart == InputParts::TemperatureToHumidity)
        {
            getMapData(temperatureToHumidity, line);
        }
        else if (inputPart == InputParts::HumidityToLocation)
        {
            getMapData(humidityToLocation, line);
        }
    }

    for (auto seed : seeds)
    {
        long long tmp  = seed;
        for (auto val : seedToSoil)
        {
            if (tmp >= val.source && tmp < (val.source + val.range))
            {
                tmp = (tmp - val.source) + val.dest;
                break;
            }
        }
        for (auto val : soilToFirtilizer)
        {
            if (tmp >= val.source && tmp < (val.source + val.range))
            {
                tmp = (tmp - val.source) + val.dest;
                break;
            }
        }
        for (auto val : firtilizerToWater)
        {
            if (tmp >= val.source && tmp < (val.source + val.range))
            {
                tmp = (tmp - val.source) + val.dest;
                break;
            }
        }
        for (auto val : waterToLight)
        {
            if (tmp >= val.source && tmp < (val.source + val.range))
            {
                tmp = (tmp - val.source) + val.dest;
                break;
            }
        }
        for (auto val : lightToTemperature)
        {
            if (tmp >= val.source && tmp < (val.source + val.range))
            {
                tmp = (tmp - val.source) + val.dest;
                break;
            }
        }
        for (auto val : temperatureToHumidity)
        {
            if (tmp >= val.source && tmp < (val.source + val.range))
            {
                tmp = (tmp - val.source) + val.dest;
                break;
            }
        }
        for (auto val : humidityToLocation)
        {
            if (tmp >= val.source && tmp < (val.source + val.range))
            {
                tmp = (tmp - val.source) + val.dest;
                break;
            }
        }
        tmp < ans ? ans = tmp : false;
    }

    std::cout << "5.1 answer: " << ans << "\n";
    return EXIT_SUCCESS;
}


int PartTwo(const std::string& file)
{

    struct Seed
    {
        long long source;
        long long range;
    };

    long long ans = LLONG_MAX;

    std::ifstream dataFile(file);

    if (!dataFile.is_open())
    {
        std::cerr << "Could not open input file '" << file << "'!\n";
        return EXIT_FAILURE;
    }

    std::string line;
    int inputPart = InputParts::Seeds;

    vector<Seed> seeds;

    vector<Map> seedToSoil;
    vector<Map> soilToFirtilizer;
    vector<Map> firtilizerToWater;
    vector<Map> waterToLight;
    vector<Map> lightToTemperature;
    vector<Map> temperatureToHumidity;
    vector<Map> humidityToLocation;

    while (std::getline(dataFile, line))
    {
        if (line.empty())
        {
            inputPart++;
        }
        else if (line.find("map:") != line.npos) {}
        else if (inputPart == InputParts::Seeds)
        {
            string seedsStr = split(line, ":")[1];
            cout << seedsStr << "\n";
            vector<string> seedsVec = split(seedsStr, " ");
            auto it = seedsVec.begin();
            while (it != seedsVec.end())
            {
                Seed seed;
                seed.source = stoll(*it);
                it++;
                seed.range =  stoll(*it);
                it++;
                seeds.push_back(seed);
            }
        }
        else if (inputPart == InputParts::SeedToSoil)
        {
            getMapData(seedToSoil, line);
        }
        else if (inputPart == InputParts::SoilToFirtilizer)
        {
            getMapData(soilToFirtilizer, line);
        }
        else if (inputPart == InputParts::FirtilizerToWater)
        {
            getMapData(firtilizerToWater, line);
        }
        else if (inputPart == InputParts::WaterToLight)
        {
            getMapData(waterToLight, line);
        }
        else if (inputPart == InputParts::LightToTemperature)
        {
            getMapData(lightToTemperature, line);
        }
        else if (inputPart == InputParts::TemperatureToHumidity)
        {
            getMapData(temperatureToHumidity, line);
        }
        else if (inputPart == InputParts::HumidityToLocation)
        {
            getMapData(humidityToLocation, line);
        }
    }

    for (auto seed : seeds)
    {
        for (auto i = seed.source; i < (seed.source + seed.range); i++)
        {
        long long tmp  = i;
        for (auto val : seedToSoil)
        {
            if (tmp >= val.source && tmp < (val.source + val.range))
            {
                tmp = (tmp - val.source) + val.dest;
                break;
            }
        }
        for (auto val : soilToFirtilizer)
        {
            if (tmp >= val.source && tmp < (val.source + val.range))
            {
                tmp = (tmp - val.source) + val.dest;
                break;
            }
        }
        for (auto val : firtilizerToWater)
        {
            if (tmp >= val.source && tmp < (val.source + val.range))
            {
                tmp = (tmp - val.source) + val.dest;
                break;
            }
        }
        for (auto val : waterToLight)
        {
            if (tmp >= val.source && tmp < (val.source + val.range))
            {
                tmp = (tmp - val.source) + val.dest;
                break;
            }
        }
        for (auto val : lightToTemperature)
        {
            if (tmp >= val.source && tmp < (val.source + val.range))
            {
                tmp = (tmp - val.source) + val.dest;
                break;
            }
        }
        for (auto val : temperatureToHumidity)
        {
            if (tmp >= val.source && tmp < (val.source + val.range))
            {
                tmp = (tmp - val.source) + val.dest;
                break;
            }
        }
        for (auto val : humidityToLocation)
        {
            if (tmp >= val.source && tmp < (val.source + val.range))
            {
                tmp = (tmp - val.source) + val.dest;
                break;
            }
        }
        tmp < ans ? ans = tmp : false;
        }
    }

    std::cout << "5.2 answer: " << ans << "\n";
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
