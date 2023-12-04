#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <array>
#include <cmath>

class Card
{
public:
    Card(std::string line, uint32_t ind);
    ~Card() {}

    uint32_t getPoints();
    uint32_t getNumberOfMatches();
    uint32_t getIndex();

private:
    uint32_t index = 0;
    std::array<uint8_t, 10> winningValues;
    std::array<uint8_t, 25> ourValues;

    void chopName(std::string &line);
    void getValues(std::string &line);
};

