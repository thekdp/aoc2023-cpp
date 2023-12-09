#include "almanac.h"

Almanac::Almanac()
{
}

void Almanac::defineSeeds(std::ifstream &input)
{
    std::string seedLine;
    std::getline(input, seedLine);
    std::istringstream stream(seedLine);
    std::string seedString;
    while(std::getline(stream, seedString, ' ')) {
        if (seedString == "seeds:")
            continue;

        seeds.push_back(std::stoull(seedString));
    }
}

void Almanac::launchFirstAlgotithm(std::ifstream &input)
{
    defineSeeds(input);
    defineMaps(input);
    printSmallestLocation();
}

void Almanac::launchSecondAlgotithm(std::ifstream &input)
{
    defineSeedRanges(input);
    defineMaps(input);
    printSmallestLocationForRanges();
}

std::vector<Converter *> Almanac::getMaps()
{
    return maps;
}

std::vector<uint64_t> Almanac::getSeeds()
{
    return seeds;
}

void Almanac::printAllValues()
{
    for (auto map : getMaps()) {
        std::cout << "Map: " << map->getName() << '\n';
        for (auto rule : map->getRules()) {
            std::cout << "Source: " << rule.source << '\n';
            std::cout << "Destin: " << rule.destination << '\n';
            std::cout << "Length: " << rule.length << '\n';
        }
        std::cout << "==============\n";
    }
}

std::vector<uint64_t> Almanac::getResultsFromSeeds()
{
    std::vector<uint64_t> results;
    for (auto seed : seeds) {
        results.push_back(convertSeed(seed));
    }
    return results;
}


void Almanac::defineMaps(std::ifstream &input)
{
    std::string line;
    Converter *map = nullptr;
    while (std::getline(input, line)) {
        std::string name;
        size_t wordPos = line.find("map");

        if (wordPos != std::string::npos) {
            name = line.substr(0, wordPos - 2);
            map = new Converter(name);
            maps.push_back(map);
            continue;
        } else if (line[0] >= '0' && line[0] <= '9') {
            map->addRule(line);
            continue;
        } else if (line.empty()) {
            continue;
        }
    }
}

void Almanac::defineSeedRanges(std::ifstream &input)
{
    std::string seedLine;
    std::getline(input, seedLine);
    std::istringstream stream(seedLine);
    std::string seedString;

    bool isValue = true;
    uint64_t seed;

    while (std::getline(stream, seedString, ' ')) {
        if (seedString == "seeds:")
            continue;
        if (isValue) {
            seed = std::stoull(seedString);
        } else {
            uint64_t last = seed;
            uint64_t length = std::stoull(seedString);
            seedRanges.push_back(SeedRange{ seed, length });
        }
        isValue = !isValue;
    }
}

uint64_t Almanac::convertSeed(uint64_t seed)
{
    for (auto map : maps) {
        seed = map->convertValue(seed);
    }
    return seed;
}

void Almanac::printSmallestLocation()
{
    std::vector<uint64_t> results = getResultsFromSeeds(); 
    for (size_t i = 0; i < results.size(); ++i) {
        std::cout << "For seed " << seeds[i] << " location is " << results[i] << '\n';
    }
    std::sort(results.begin(), results.end());
    std::cout << '\n' << "Smallest location number: " << results[0] << '\n';
}

void Almanac::printSmallestLocationForRanges()
{
    int32_t threadsNum = std::thread::hardware_concurrency();
    while (seedRanges.size() < threadsNum) {
        std::sort(seedRanges.begin(), seedRanges.end(), [=](SeedRange &left, SeedRange &right)
        {
            return right.length < left.length;
        });
        SeedRange range = seedRanges.back();
        seedRanges.pop_back();

        uint64_t halfLength = range.length / 2;
        seedRanges.push_back(SeedRange{ range.seed, halfLength });
        seedRanges.push_back(SeedRange{ range.seed + halfLength, range.length - halfLength });
    }

    std::vector<std::thread> threads;
    uint64_t result = std::numeric_limits<uint64_t>::max();

    std::mutex mutex;
    for (size_t i = 0; i < seedRanges.size(); ++i) {
        threads.emplace_back([i, this, &result, &mutex]()
        {
            for (size_t j = 0; j < seedRanges[i].length; ++j) {
                uint64_t newResult = convertSeed(seedRanges[i].seed + j);
                if (newResult < result) {

                    std::lock_guard<std::mutex> lock(mutex);
                    result = newResult;
                    std::cout << "Result: " << result << " for seed: " << seedRanges[i].seed + j << '\n';
                }
            }
        });

    }

    for (auto &thread : threads) {
        thread.join();
    }
    std::cout << "result: " << result << '\n';
}
