#pragma once

#include "converter.h"

struct SeedRange
{
    uint64_t seed;
    uint64_t length;
};

class Almanac
{
public:
    Almanac();
    ~Almanac() {}

    void launchFirstAlgotithm(std::ifstream &input);
    void launchSecondAlgotithm(std::ifstream &input);

    std::vector<Converter *> getMaps();
    std::vector<uint64_t> getSeeds();
    void printAllValues();
    std::vector<uint64_t> getResultsFromSeeds();
private:

    std::vector<uint64_t> seeds;
    std::vector<SeedRange> seedRanges;
    std::vector<Converter *> maps;

    void defineSeeds(std::ifstream &input);
    void defineMaps(std::ifstream &input);
    void defineSeedRanges(std::ifstream &input);
    uint64_t convertSeed(uint64_t seed);
    uint64_t getSmallestConversionForSeedRange(uint64_t seed, uint64_t range);
    void printSmallestLocation();
    void printSmallestLocationForRanges();
};