#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "card.h"

class CardPile
{
public:
    CardPile(std::ifstream &input);
    ~CardPile() {}

    uint32_t calculateTotalPoints();
    uint32_t calculateScratchCards(uint32_t index);
private:
    void readInput(std::ifstream &input);

    std::vector<Card *> cards = {};
    std::array<uint32_t, 220> copies;
};